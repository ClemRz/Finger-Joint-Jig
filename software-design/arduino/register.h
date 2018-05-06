#ifndef _REGISTER_H
#define _REGISTER_H

#define REG_MAP_SIZE  16  // Size of the register (consider nuber of bytes)

typedef struct {
  union {
    byte byteAt[REG_MAP_SIZE];
    struct {                            // bytes:
      double kerfMm;                    // 4
      double fingerMm;                  // 4
      double toleranceUm;               // 4
      double offsetMm;                  // 4
    };
  };
} Register;

#endif  //_REGISTER_H
