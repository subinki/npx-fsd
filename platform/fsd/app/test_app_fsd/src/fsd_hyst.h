#ifndef FSD_HYST_H
#define FSD_HYST_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FSD_NO_DECISION = 0,
    FSD_REAL,
    FSD_FAKE
} fsd_result_t;

static inline uint16_t fsd_voltage_to_code12(float v) {
    if (v <= 0.0f) return 0;
    if (v >= 1.0f) return 4095;
    return (uint16_t)(v * 4095.0f + 0.5f);
}

typedef struct {
    uint16_t thr_over;          
    uint16_t min_peak;          
    uint16_t min_over_count;    

    uint16_t thr_high;          
    uint16_t thr_low;           
    uint16_t min_dwell;         

    uint8_t  zeros_for_boundary;
} fsd_hyst_config_t;

typedef struct {
    fsd_hyst_config_t cfg;
    bool     cycle_active;
    uint16_t peak;
    uint16_t over_count;

    bool     in_high;
    uint16_t dwell;

    uint8_t  zero_run;
} fsd_hyst_detector_t;

static inline void fsd_hyst_default_config(fsd_hyst_config_t* c,
        float thr_over_v, float min_peak_v,
        float high_v, float low_v,
        uint16_t min_over_count, uint16_t min_dwell,
        uint8_t zeros_for_boundary)
{
    c->thr_over          = fsd_voltage_to_code12(thr_over_v);
    c->min_peak          = fsd_voltage_to_code12(min_peak_v);
    c->thr_high          = fsd_voltage_to_code12(high_v);
    c->thr_low           = fsd_voltage_to_code12(low_v);
    c->min_over_count    = min_over_count;
    c->min_dwell         = min_dwell;
    c->zeros_for_boundary= (zeros_for_boundary==0)?1:zeros_for_boundary;
}

void fsd_hyst_init(fsd_hyst_detector_t* d, const fsd_hyst_config_t* cfg);

fsd_result_t fsd_hyst_feed_sample(fsd_hyst_detector_t* d, uint16_t raw16);

#ifdef __cplusplus
}
#endif
#endif // FSD_HYST_H

