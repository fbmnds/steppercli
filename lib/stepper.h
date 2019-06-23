#ifndef LIB_STEPPER_H_
#define LIB_STEPPER_H_


typedef enum {
    X;
    Y;
    Z;
#ifdef XA_AXIS
    XA;
#endif
#ifdef XA_AXIS
    YA;
#endif
#ifdef XA_AXIS
    ZA;
#endif
} axis_t;

typedef enum {
    Forward = 1;
    Backward = 0;
} direction_t;

typedef struct {
    axis_t      axis;
    direction_t dir;
    unit16_t    steps;
    uint16_t    freq;
} st_block_t;


#endif /* LIB_STEPPER_H_ */
