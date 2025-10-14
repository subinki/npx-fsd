#ifndef FSD_H
#define FSD_H

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

static inline uint16_t fsd_voltage_to_code12(float v){
    if (v <= 0.0f) return 0;
    if (v >= 1.0f) return 4095;
    return (uint16_t)(v * 4095.0f + 0.5f);
}

// ------------------- Config -------------------
typedef struct {
    uint16_t thr_over;        
    uint16_t min_peak;        
    uint16_t min_over_count;  
    uint16_t thr_high;        
    uint16_t thr_low;         
    uint16_t min_dwell;       

    uint16_t fake_peak_max;   

    uint16_t window_samples;  
} fsd_config_t;

// ------------------- State -------------------
typedef struct {
    fsd_config_t cfg;

    bool     cycle_active;
    uint16_t peak;
    uint16_t over_count;

    bool     in_high;
    uint16_t dwell;

    uint16_t samples_in_cycle;
    uint16_t min_val;
    uint16_t max_val;
} fsd_t;

// ------------------- API -------------------
static inline void fsd_default_config(fsd_config_t* c){
    c->thr_over        = fsd_voltage_to_code12(0.70f);
    c->min_peak        = fsd_voltage_to_code12(0.90f);
    c->min_over_count  = 3;
    c->thr_high        = fsd_voltage_to_code12(0.70f);
    c->thr_low         = fsd_voltage_to_code12(0.55f);
    c->min_dwell       = 2;
    c->fake_peak_max   = fsd_voltage_to_code12(0.70f);
    c->window_samples  = 5;  
}

void fsd_init(fsd_t* d, const fsd_config_t* cfg);
fsd_result_t fsd_feed_sample(fsd_t* d, uint16_t raw16);

#ifdef __cplusplus
}
#endif
#endif // FSD_H

