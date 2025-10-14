#include "fsd.h"

static inline uint16_t code12_from_raw(uint16_t raw16){
    return (uint16_t)((raw16 >> 4) & 0x0FFFu);
}

static inline fsd_result_t decide_and_reset(fsd_t* d){
    fsd_result_t out = FSD_FAKE; 

    if (d->cycle_active) {
        bool cond_peak_count = (d->peak >= d->cfg.min_peak) &&
                               (d->over_count >= d->cfg.min_over_count);
        bool cond_dwell = (d->dwell >= d->cfg.min_dwell);

        if (cond_peak_count && cond_dwell) {
            out = FSD_REAL;
        } else {
            if (d->peak < d->cfg.fake_peak_max) {
                out = FSD_FAKE;
            } else {
                uint16_t range = d->max_val - d->min_val;
                if (range < fsd_voltage_to_code12(0.08f)) {
                    out = FSD_FAKE;
                }
            }
        }
    } else {
        out = FSD_FAKE;
    }

    d->cycle_active    = false;
    d->peak            = 0;
    d->over_count      = 0;
    d->in_high         = false;
    d->dwell           = 0;
    d->samples_in_cycle= 0;
    d->min_val         = 4095;
    d->max_val         = 0;

    return out;
}

void fsd_init(fsd_t* d, const fsd_config_t* cfg){
    d->cfg = *cfg;
    d->cycle_active    = false;
    d->peak            = 0;
    d->over_count      = 0;
    d->in_high         = false;
    d->dwell           = 0;
    d->samples_in_cycle= 0;
    d->min_val         = 4095;
    d->max_val         = 0;
}

fsd_result_t fsd_feed_sample(fsd_t* d, uint16_t raw16){
    uint16_t s = code12_from_raw(raw16);

    d->cycle_active = true;
    d->samples_in_cycle++;

    if (s > d->peak) d->peak = s;

    if (s < d->min_val) d->min_val = s;
    if (s > d->max_val) d->max_val = s;

    if (s >= d->cfg.thr_over) d->over_count++;

    if (!d->in_high) {
        if (s >= d->cfg.thr_high) {
            d->in_high = true;
            d->dwell   = 1;
        }
    } else {
        if (s <= d->cfg.thr_low) {
            d->in_high = false;
        } else {
            d->dwell++;
        }
    }

    if (d->samples_in_cycle >= d->cfg.window_samples) {
        return decide_and_reset(d);
    }

    return FSD_NO_DECISION;
}

