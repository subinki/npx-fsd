#include "fsd_simple.h"

static inline uint16_t code12_from_raw(uint16_t raw16) {
    return (uint16_t)((raw16 >> 4) & 0x0FFFu);
}

void fsd_simple_init(fsd_simple_detector_t* d, const fsd_simple_config_t* cfg){
    d->cfg = *cfg;
    d->cycle_active = false;
    d->peak = 0;
    d->over_count = 0;
    d->zero_run = 0;
}

static inline fsd_result_t decide_and_reset(fsd_simple_detector_t* d) {
    fsd_result_t out = FSD_NO_DECISION;
    if (d->cycle_active) {
        bool pass = (d->over_count >= d->cfg.min_over_count) &&
                    (d->peak >= d->cfg.min_peak);
        out = pass ? FSD_REAL : FSD_FAKE;
    }
    d->cycle_active = false;
    d->peak = 0;
    d->over_count = 0;
    d->zero_run = 0;
    return out;
}

fsd_result_t fsd_simple_feed_sample(fsd_simple_detector_t* d, uint16_t raw16){
    uint16_t s = code12_from_raw(raw16);

    if (s == 0u) {
        if (++d->zero_run >= d->cfg.zeros_for_boundary) {
            return decide_and_reset(d);
        }
        return FSD_NO_DECISION;
    }

    d->zero_run = 0;
    d->cycle_active = true;

    if (s > d->peak) d->peak = s;
    if (s >= d->cfg.thr_over) d->over_count++;

    return FSD_NO_DECISION;
}
