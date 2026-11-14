/*
MIT License

Copyright (c) 2026 Christian Luppi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <lm2/misc/lm2_noise.h>
#include <lm2/scalar/lm2_safe_ops.h>
#include <lm2/scalar/lm2_scalar.h>

// The public safe arithmetic functions intentionally reject subnormal results.
// Noise coordinates are checked for finiteness by lm2_floor_f32/f64, and all
// calculations below use bounded local cell coordinates, gradients, or hash
// fractions. Subnormal intermediates are valid here and may underflow to zero.
static double _lm2_noise_add_f64(double a, double b) {
  return a + b;
}
static float _lm2_noise_add_f32(float a, float b) {
  return a + b;
}
static double _lm2_noise_sub_f64(double a, double b) {
  return a - b;
}
static float _lm2_noise_sub_f32(float a, float b) {
  return a - b;
}
static double _lm2_noise_mul_f64(double a, double b) {
  return a * b;
}
static float _lm2_noise_mul_f32(float a, float b) {
  return a * b;
}
static double _lm2_noise_div_f64(double a, double b) {
  return a / b;
}
static float _lm2_noise_div_f32(float a, float b) {
  return a / b;
}
static double _lm2_noise_lerp_f64(double a, double t, double b) {
  return a + t * (b - a);
}
static float _lm2_noise_lerp_f32(float a, float t, float b) {
  return a + t * (b - a);
}

// =============================================================================
// Permutation Table (Ken Perlin's standard table, repeated for wrapping)
// =============================================================================

static const unsigned char _lm2_perm[512] = {
    151,
    160,
    137,
    91,
    90,
    15,
    131,
    13,
    201,
    95,
    96,
    53,
    194,
    233,
    7,
    225,
    140,
    36,
    103,
    30,
    69,
    142,
    8,
    99,
    37,
    240,
    21,
    10,
    23,
    190,
    6,
    148,
    247,
    120,
    234,
    75,
    0,
    26,
    197,
    62,
    94,
    252,
    219,
    203,
    117,
    35,
    11,
    32,
    57,
    177,
    33,
    88,
    237,
    149,
    56,
    87,
    174,
    20,
    125,
    136,
    171,
    168,
    68,
    175,
    74,
    165,
    71,
    134,
    139,
    48,
    27,
    166,
    77,
    146,
    158,
    231,
    83,
    111,
    229,
    122,
    60,
    211,
    133,
    230,
    220,
    105,
    92,
    41,
    55,
    46,
    245,
    40,
    244,
    102,
    143,
    54,
    65,
    25,
    63,
    161,
    1,
    216,
    80,
    73,
    209,
    76,
    132,
    187,
    208,
    89,
    18,
    169,
    200,
    196,
    135,
    130,
    116,
    188,
    159,
    86,
    164,
    100,
    109,
    198,
    173,
    186,
    3,
    64,
    52,
    217,
    226,
    250,
    124,
    123,
    5,
    202,
    38,
    147,
    118,
    126,
    255,
    82,
    85,
    212,
    207,
    206,
    59,
    227,
    47,
    16,
    58,
    17,
    182,
    189,
    28,
    42,
    223,
    183,
    170,
    213,
    119,
    248,
    152,
    2,
    44,
    154,
    163,
    70,
    221,
    153,
    101,
    155,
    167,
    43,
    172,
    9,
    129,
    22,
    39,
    253,
    19,
    98,
    108,
    110,
    79,
    113,
    224,
    232,
    178,
    185,
    112,
    104,
    218,
    246,
    97,
    228,
    251,
    34,
    242,
    193,
    238,
    210,
    144,
    12,
    191,
    179,
    162,
    241,
    81,
    51,
    145,
    235,
    249,
    14,
    239,
    107,
    49,
    192,
    214,
    31,
    181,
    199,
    106,
    157,
    184,
    84,
    204,
    176,
    115,
    121,
    50,
    45,
    127,
    4,
    150,
    254,
    138,
    236,
    205,
    93,
    222,
    114,
    67,
    29,
    24,
    72,
    243,
    141,
    128,
    195,
    78,
    66,
    215,
    61,
    156,
    180,
    151,
    160,
    137,
    91,
    90,
    15,
    131,
    13,
    201,
    95,
    96,
    53,
    194,
    233,
    7,
    225,
    140,
    36,
    103,
    30,
    69,
    142,
    8,
    99,
    37,
    240,
    21,
    10,
    23,
    190,
    6,
    148,
    247,
    120,
    234,
    75,
    0,
    26,
    197,
    62,
    94,
    252,
    219,
    203,
    117,
    35,
    11,
    32,
    57,
    177,
    33,
    88,
    237,
    149,
    56,
    87,
    174,
    20,
    125,
    136,
    171,
    168,
    68,
    175,
    74,
    165,
    71,
    134,
    139,
    48,
    27,
    166,
    77,
    146,
    158,
    231,
    83,
    111,
    229,
    122,
    60,
    211,
    133,
    230,
    220,
    105,
    92,
    41,
    55,
    46,
    245,
    40,
    244,
    102,
    143,
    54,
    65,
    25,
    63,
    161,
    1,
    216,
    80,
    73,
    209,
    76,
    132,
    187,
    208,
    89,
    18,
    169,
    200,
    196,
    135,
    130,
    116,
    188,
    159,
    86,
    164,
    100,
    109,
    198,
    173,
    186,
    3,
    64,
    52,
    217,
    226,
    250,
    124,
    123,
    5,
    202,
    38,
    147,
    118,
    126,
    255,
    82,
    85,
    212,
    207,
    206,
    59,
    227,
    47,
    16,
    58,
    17,
    182,
    189,
    28,
    42,
    223,
    183,
    170,
    213,
    119,
    248,
    152,
    2,
    44,
    154,
    163,
    70,
    221,
    153,
    101,
    155,
    167,
    43,
    172,
    9,
    129,
    22,
    39,
    253,
    19,
    98,
    108,
    110,
    79,
    113,
    224,
    232,
    178,
    185,
    112,
    104,
    218,
    246,
    97,
    228,
    251,
    34,
    242,
    193,
    238,
    210,
    144,
    12,
    191,
    179,
    162,
    241,
    81,
    51,
    145,
    235,
    249,
    14,
    239,
    107,
    49,
    192,
    214,
    31,
    181,
    199,
    106,
    157,
    184,
    84,
    204,
    176,
    115,
    121,
    50,
    45,
    127,
    4,
    150,
    254,
    138,
    236,
    205,
    93,
    222,
    114,
    67,
    29,
    24,
    72,
    243,
    141,
    128,
    195,
    78,
    66,
    215,
    61,
    156,
    180};

// =============================================================================
// Internal Helpers (Perlin Fade Curve)
// =============================================================================

// Fade: 6t^5 - 15t^4 + 10t^3 = t^3 * (t * (t * 6 - 15) + 10)
static double _lm2_fade_f64(double t) {
  return _lm2_noise_mul_f64(
      _lm2_noise_mul_f64(_lm2_noise_mul_f64(t, t), t),
      _lm2_noise_add_f64(_lm2_noise_mul_f64(t, _lm2_noise_sub_f64(_lm2_noise_mul_f64(t, 6.0), 15.0)), 10.0));
}

static float _lm2_fade_f32(float t) {
  return _lm2_noise_mul_f32(
      _lm2_noise_mul_f32(_lm2_noise_mul_f32(t, t), t),
      _lm2_noise_add_f32(_lm2_noise_mul_f32(t, _lm2_noise_sub_f32(_lm2_noise_mul_f32(t, 6.0f), 15.0f)), 10.0f));
}

// =============================================================================
// Internal Helpers (Perlin Gradient Functions)
// =============================================================================

// 2D gradient: 4 directions (1,1), (1,-1), (-1,1), (-1,-1)
static double _lm2_grad2d_f64(int hash, double x, double y) {
  switch (hash & 3) {
    case 0:  return _lm2_noise_add_f64(x, y);
    case 1:  return _lm2_noise_sub_f64(x, y);
    case 2:  return _lm2_noise_sub_f64(y, x);
    default: return _lm2_noise_sub_f64(0.0, _lm2_noise_add_f64(x, y));
  }
}

static float _lm2_grad2d_f32(int hash, float x, float y) {
  switch (hash & 3) {
    case 0:  return _lm2_noise_add_f32(x, y);
    case 1:  return _lm2_noise_sub_f32(x, y);
    case 2:  return _lm2_noise_sub_f32(y, x);
    default: return _lm2_noise_sub_f32(0.0f, _lm2_noise_add_f32(x, y));
  }
}

// 3D gradient: Ken Perlin's improved gradient selection (12 directions)
static double _lm2_grad3d_f64(int hash, double x, double y, double z) {
  int h = hash & 15;
  double u = (h < 8) ? x : y;
  double v = (h < 4) ? y : ((h == 12 || h == 14) ? x : z);
  return _lm2_noise_add_f64(
      (h & 1) ? _lm2_noise_sub_f64(0.0, u) : u,
      (h & 2) ? _lm2_noise_sub_f64(0.0, v) : v);
}

static float _lm2_grad3d_f32(int hash, float x, float y, float z) {
  int h = hash & 15;
  float u = (h < 8) ? x : y;
  float v = (h < 4) ? y : ((h == 12 || h == 14) ? x : z);
  return _lm2_noise_add_f32(
      (h & 1) ? _lm2_noise_sub_f32(0.0f, u) : u,
      (h & 2) ? _lm2_noise_sub_f32(0.0f, v) : v);
}

// =============================================================================
// Internal Helpers (Voronoi Hash Functions)
// =============================================================================

// Integer hash for cell-based random values (overflow is intentional)
static uint32_t _lm2_noise_hash(uint32_t x, uint32_t y, uint32_t seed) {
  uint32_t h = x * 374761393u + y * 668265263u + seed;
  h = (h ^ (h >> 13)) * 1274126177u;
  return h ^ (h >> 16);
}

static uint32_t _lm2_noise_hash3(uint32_t x, uint32_t y, uint32_t z, uint32_t seed) {
  uint32_t h = x * 374761393u + y * 668265263u + z * 1103515245u + seed;
  h = (h ^ (h >> 13)) * 1274126177u;
  return h ^ (h >> 16);
}

// Convert hash to [0, 1) range
static double _lm2_hash_to_f64(uint32_t h) {
  return _lm2_noise_div_f64((double)(h & 0x7FFFFFFFu), (double)0x7FFFFFFFu);
}

static float _lm2_hash_to_f32(uint32_t h) {
  return _lm2_noise_div_f32((float)(h & 0x7FFFFFFFu), (float)0x7FFFFFFFu);
}

// =============================================================================
// Perlin Noise 2D
// =============================================================================

// Reduce before converting to int: finite coordinates can exceed INT_MAX.
static int _lm2_perlin_cell_f64(double cell) {
  int wrapped = (int)fmod(cell, 256.0);
  return wrapped < 0 ? wrapped + 256 : wrapped;
}

static int _lm2_perlin_cell_f32(float cell) {
  int wrapped = (int)fmodf(cell, 256.0f);
  return wrapped < 0 ? wrapped + 256 : wrapped;
}

LM2_API double lm2_perlin2_f64(double x, double y) {
  double xf_d = lm2_floor_f64(x);
  double yf_d = lm2_floor_f64(y);
  int xi = _lm2_perlin_cell_f64(xf_d);
  int yi = _lm2_perlin_cell_f64(yf_d);

  double xf = _lm2_noise_sub_f64(x, xf_d);
  double yf = _lm2_noise_sub_f64(y, yf_d);

  double u = _lm2_fade_f64(xf);
  double v = _lm2_fade_f64(yf);

  int aa = _lm2_perm[_lm2_perm[xi] + yi];
  int ab = _lm2_perm[_lm2_perm[xi] + yi + 1];
  int ba = _lm2_perm[_lm2_perm[xi + 1] + yi];
  int bb = _lm2_perm[_lm2_perm[xi + 1] + yi + 1];

  double g00 = _lm2_grad2d_f64(aa, xf, yf);
  double g10 = _lm2_grad2d_f64(ba, _lm2_noise_sub_f64(xf, 1.0), yf);
  double g01 = _lm2_grad2d_f64(ab, xf, _lm2_noise_sub_f64(yf, 1.0));
  double g11 = _lm2_grad2d_f64(bb, _lm2_noise_sub_f64(xf, 1.0), _lm2_noise_sub_f64(yf, 1.0));

  double x0 = _lm2_noise_lerp_f64(g00, u, g10);
  double x1 = _lm2_noise_lerp_f64(g01, u, g11);
  return _lm2_noise_lerp_f64(x0, v, x1);
}

LM2_API float lm2_perlin2_f32(float x, float y) {
  float xf_d = lm2_floor_f32(x);
  float yf_d = lm2_floor_f32(y);
  int xi = _lm2_perlin_cell_f32(xf_d);
  int yi = _lm2_perlin_cell_f32(yf_d);

  float xf = _lm2_noise_sub_f32(x, xf_d);
  float yf = _lm2_noise_sub_f32(y, yf_d);

  float u = _lm2_fade_f32(xf);
  float v = _lm2_fade_f32(yf);

  int aa = _lm2_perm[_lm2_perm[xi] + yi];
  int ab = _lm2_perm[_lm2_perm[xi] + yi + 1];
  int ba = _lm2_perm[_lm2_perm[xi + 1] + yi];
  int bb = _lm2_perm[_lm2_perm[xi + 1] + yi + 1];

  float g00 = _lm2_grad2d_f32(aa, xf, yf);
  float g10 = _lm2_grad2d_f32(ba, _lm2_noise_sub_f32(xf, 1.0f), yf);
  float g01 = _lm2_grad2d_f32(ab, xf, _lm2_noise_sub_f32(yf, 1.0f));
  float g11 = _lm2_grad2d_f32(bb, _lm2_noise_sub_f32(xf, 1.0f), _lm2_noise_sub_f32(yf, 1.0f));

  float x0 = _lm2_noise_lerp_f32(g00, u, g10);
  float x1 = _lm2_noise_lerp_f32(g01, u, g11);
  return _lm2_noise_lerp_f32(x0, v, x1);
}

// =============================================================================
// Perlin Noise 3D
// =============================================================================

LM2_API double lm2_perlin3_f64(double x, double y, double z) {
  double xf_d = lm2_floor_f64(x);
  double yf_d = lm2_floor_f64(y);
  double zf_d = lm2_floor_f64(z);
  int xi = _lm2_perlin_cell_f64(xf_d);
  int yi = _lm2_perlin_cell_f64(yf_d);
  int zi = _lm2_perlin_cell_f64(zf_d);

  double xf = _lm2_noise_sub_f64(x, xf_d);
  double yf = _lm2_noise_sub_f64(y, yf_d);
  double zf = _lm2_noise_sub_f64(z, zf_d);

  double u = _lm2_fade_f64(xf);
  double v = _lm2_fade_f64(yf);
  double w = _lm2_fade_f64(zf);

  int a = _lm2_perm[xi] + yi;
  int aa = _lm2_perm[a] + zi;
  int ab = _lm2_perm[a + 1] + zi;
  int b = _lm2_perm[xi + 1] + yi;
  int ba = _lm2_perm[b] + zi;
  int bb = _lm2_perm[b + 1] + zi;

  double x1f = _lm2_noise_sub_f64(xf, 1.0);
  double y1f = _lm2_noise_sub_f64(yf, 1.0);
  double z1f = _lm2_noise_sub_f64(zf, 1.0);

  double g000 = _lm2_grad3d_f64(_lm2_perm[aa], xf, yf, zf);
  double g100 = _lm2_grad3d_f64(_lm2_perm[ba], x1f, yf, zf);
  double g010 = _lm2_grad3d_f64(_lm2_perm[ab], xf, y1f, zf);
  double g110 = _lm2_grad3d_f64(_lm2_perm[bb], x1f, y1f, zf);
  double g001 = _lm2_grad3d_f64(_lm2_perm[aa + 1], xf, yf, z1f);
  double g101 = _lm2_grad3d_f64(_lm2_perm[ba + 1], x1f, yf, z1f);
  double g011 = _lm2_grad3d_f64(_lm2_perm[ab + 1], xf, y1f, z1f);
  double g111 = _lm2_grad3d_f64(_lm2_perm[bb + 1], x1f, y1f, z1f);

  double lx0 = _lm2_noise_lerp_f64(g000, u, g100);
  double lx1 = _lm2_noise_lerp_f64(g010, u, g110);
  double lx2 = _lm2_noise_lerp_f64(g001, u, g101);
  double lx3 = _lm2_noise_lerp_f64(g011, u, g111);

  double ly0 = _lm2_noise_lerp_f64(lx0, v, lx1);
  double ly1 = _lm2_noise_lerp_f64(lx2, v, lx3);

  return _lm2_noise_lerp_f64(ly0, w, ly1);
}

LM2_API float lm2_perlin3_f32(float x, float y, float z) {
  float xf_d = lm2_floor_f32(x);
  float yf_d = lm2_floor_f32(y);
  float zf_d = lm2_floor_f32(z);
  int xi = _lm2_perlin_cell_f32(xf_d);
  int yi = _lm2_perlin_cell_f32(yf_d);
  int zi = _lm2_perlin_cell_f32(zf_d);

  float xf = _lm2_noise_sub_f32(x, xf_d);
  float yf = _lm2_noise_sub_f32(y, yf_d);
  float zf = _lm2_noise_sub_f32(z, zf_d);

  float u = _lm2_fade_f32(xf);
  float v = _lm2_fade_f32(yf);
  float w = _lm2_fade_f32(zf);

  int a = _lm2_perm[xi] + yi;
  int aa = _lm2_perm[a] + zi;
  int ab = _lm2_perm[a + 1] + zi;
  int b = _lm2_perm[xi + 1] + yi;
  int ba = _lm2_perm[b] + zi;
  int bb = _lm2_perm[b + 1] + zi;

  float x1f = _lm2_noise_sub_f32(xf, 1.0f);
  float y1f = _lm2_noise_sub_f32(yf, 1.0f);
  float z1f = _lm2_noise_sub_f32(zf, 1.0f);

  float g000 = _lm2_grad3d_f32(_lm2_perm[aa], xf, yf, zf);
  float g100 = _lm2_grad3d_f32(_lm2_perm[ba], x1f, yf, zf);
  float g010 = _lm2_grad3d_f32(_lm2_perm[ab], xf, y1f, zf);
  float g110 = _lm2_grad3d_f32(_lm2_perm[bb], x1f, y1f, zf);
  float g001 = _lm2_grad3d_f32(_lm2_perm[aa + 1], xf, yf, z1f);
  float g101 = _lm2_grad3d_f32(_lm2_perm[ba + 1], x1f, yf, z1f);
  float g011 = _lm2_grad3d_f32(_lm2_perm[ab + 1], xf, y1f, z1f);
  float g111 = _lm2_grad3d_f32(_lm2_perm[bb + 1], x1f, y1f, z1f);

  float lx0 = _lm2_noise_lerp_f32(g000, u, g100);
  float lx1 = _lm2_noise_lerp_f32(g010, u, g110);
  float lx2 = _lm2_noise_lerp_f32(g001, u, g101);
  float lx3 = _lm2_noise_lerp_f32(g011, u, g111);

  float ly0 = _lm2_noise_lerp_f32(lx0, v, lx1);
  float ly1 = _lm2_noise_lerp_f32(lx2, v, lx3);

  return _lm2_noise_lerp_f32(ly0, w, ly1);
}

// =============================================================================
// Voronoi Noise 2D
// =============================================================================

// The hash uses 32-bit modular arithmetic; wrap in floating point before the
// conversion so even finite coordinates outside the signed integer range work.
static uint32_t _lm2_voronoi_cell(double cell) {
  double wrapped = fmod(cell, 4294967296.0);
  if (wrapped < 0.0) wrapped += 4294967296.0;
  return (uint32_t)wrapped;
}

LM2_API double lm2_voronoi2_f64(double x, double y) {
  double xf_d = lm2_floor_f64(x);
  double yf_d = lm2_floor_f64(y);
  uint32_t xi = _lm2_voronoi_cell(xf_d);
  uint32_t yi = _lm2_voronoi_cell(yf_d);
  double xf = _lm2_noise_sub_f64(x, xf_d);
  double yf = _lm2_noise_sub_f64(y, yf_d);

  double min_dist = 1e20;

  // The nearest feature can lie two cells away along an axis. A feature in
  // the current cell is within sqrt(2), so no more distant cell is needed.
  for (int dy = -2; dy <= 2; dy++) {
    for (int dx = -2; dx <= 2; dx++) {
      double x_gap = xf < dx ? dx - xf : (xf > dx + 1 ? xf - (dx + 1) : 0.0);
      double y_gap = yf < dy ? dy - yf : (yf > dy + 1 ? yf - (dy + 1) : 0.0);
      if (x_gap >= min_dist || y_gap >= min_dist) continue;
      uint32_t cx = xi + (uint32_t)dx;
      uint32_t cy = yi + (uint32_t)dy;

      double fx = _lm2_noise_add_f64((double)dx, _lm2_hash_to_f64(_lm2_noise_hash(cx, cy, 0u)));
      double fy = _lm2_noise_add_f64((double)dy, _lm2_hash_to_f64(_lm2_noise_hash(cx, cy, 1u)));

      double ddx = _lm2_noise_sub_f64(xf, fx);
      double ddy = _lm2_noise_sub_f64(yf, fy);
      // hypot retains small representable distances when squaring would
      // underflow, including very close approaches to a feature point.
      double dist = hypot(ddx, ddy);

      if (dist < min_dist) {
        min_dist = dist;
      }
    }
  }

  return min_dist;
}

LM2_API float lm2_voronoi2_f32(float x, float y) {
  float xf_d = lm2_floor_f32(x);
  float yf_d = lm2_floor_f32(y);
  uint32_t xi = _lm2_voronoi_cell(xf_d);
  uint32_t yi = _lm2_voronoi_cell(yf_d);
  float xf = _lm2_noise_sub_f32(x, xf_d);
  float yf = _lm2_noise_sub_f32(y, yf_d);

  float min_dist = 1e20f;

  for (int dy = -2; dy <= 2; dy++) {
    for (int dx = -2; dx <= 2; dx++) {
      float x_gap = xf < dx ? dx - xf : (xf > dx + 1 ? xf - (dx + 1) : 0.0f);
      float y_gap = yf < dy ? dy - yf : (yf > dy + 1 ? yf - (dy + 1) : 0.0f);
      if (x_gap >= min_dist || y_gap >= min_dist) continue;
      uint32_t cx = xi + (uint32_t)dx;
      uint32_t cy = yi + (uint32_t)dy;

      float fx = _lm2_noise_add_f32((float)dx, _lm2_hash_to_f32(_lm2_noise_hash(cx, cy, 0u)));
      float fy = _lm2_noise_add_f32((float)dy, _lm2_hash_to_f32(_lm2_noise_hash(cx, cy, 1u)));

      float ddx = _lm2_noise_sub_f32(xf, fx);
      float ddy = _lm2_noise_sub_f32(yf, fy);
      float dist = hypotf(ddx, ddy);

      if (dist < min_dist) {
        min_dist = dist;
      }
    }
  }

  return min_dist;
}

// =============================================================================
// Voronoi Noise 3D
// =============================================================================

LM2_API double lm2_voronoi3_f64(double x, double y, double z) {
  double xf_d = lm2_floor_f64(x);
  double yf_d = lm2_floor_f64(y);
  double zf_d = lm2_floor_f64(z);
  uint32_t xi = _lm2_voronoi_cell(xf_d);
  uint32_t yi = _lm2_voronoi_cell(yf_d);
  uint32_t zi = _lm2_voronoi_cell(zf_d);
  double xf = _lm2_noise_sub_f64(x, xf_d);
  double yf = _lm2_noise_sub_f64(y, yf_d);
  double zf = _lm2_noise_sub_f64(z, zf_d);

  double min_dist = 1e20;

  // The current cell bounds the nearest distance by sqrt(3), so the second
  // ring is sufficient. Skip cells whose axis-aligned bounds are too far away.
  for (int dz = -2; dz <= 2; dz++) {
    for (int dy = -2; dy <= 2; dy++) {
      for (int dx = -2; dx <= 2; dx++) {
        double x_gap = xf < dx ? dx - xf : (xf > dx + 1 ? xf - (dx + 1) : 0.0);
        double y_gap = yf < dy ? dy - yf : (yf > dy + 1 ? yf - (dy + 1) : 0.0);
        double z_gap = zf < dz ? dz - zf : (zf > dz + 1 ? zf - (dz + 1) : 0.0);
        if (x_gap >= min_dist || y_gap >= min_dist || z_gap >= min_dist) continue;
        uint32_t cx = xi + (uint32_t)dx;
        uint32_t cy = yi + (uint32_t)dy;
        uint32_t cz = zi + (uint32_t)dz;

        double fx = _lm2_noise_add_f64((double)dx, _lm2_hash_to_f64(_lm2_noise_hash3(cx, cy, cz, 0u)));
        double fy = _lm2_noise_add_f64((double)dy, _lm2_hash_to_f64(_lm2_noise_hash3(cx, cy, cz, 1u)));
        double fz = _lm2_noise_add_f64((double)dz, _lm2_hash_to_f64(_lm2_noise_hash3(cx, cy, cz, 2u)));

        double ddx = _lm2_noise_sub_f64(xf, fx);
        double ddy = _lm2_noise_sub_f64(yf, fy);
        double ddz = _lm2_noise_sub_f64(zf, fz);
        double dist = hypot(hypot(ddx, ddy), ddz);

        if (dist < min_dist) {
          min_dist = dist;
        }
      }
    }
  }

  return min_dist;
}

LM2_API float lm2_voronoi3_f32(float x, float y, float z) {
  float xf_d = lm2_floor_f32(x);
  float yf_d = lm2_floor_f32(y);
  float zf_d = lm2_floor_f32(z);
  uint32_t xi = _lm2_voronoi_cell(xf_d);
  uint32_t yi = _lm2_voronoi_cell(yf_d);
  uint32_t zi = _lm2_voronoi_cell(zf_d);
  float xf = _lm2_noise_sub_f32(x, xf_d);
  float yf = _lm2_noise_sub_f32(y, yf_d);
  float zf = _lm2_noise_sub_f32(z, zf_d);

  float min_dist = 1e20f;

  for (int dz = -2; dz <= 2; dz++) {
    for (int dy = -2; dy <= 2; dy++) {
      for (int dx = -2; dx <= 2; dx++) {
        float x_gap = xf < dx ? dx - xf : (xf > dx + 1 ? xf - (dx + 1) : 0.0f);
        float y_gap = yf < dy ? dy - yf : (yf > dy + 1 ? yf - (dy + 1) : 0.0f);
        float z_gap = zf < dz ? dz - zf : (zf > dz + 1 ? zf - (dz + 1) : 0.0f);
        if (x_gap >= min_dist || y_gap >= min_dist || z_gap >= min_dist) continue;
        uint32_t cx = xi + (uint32_t)dx;
        uint32_t cy = yi + (uint32_t)dy;
        uint32_t cz = zi + (uint32_t)dz;

        float fx = _lm2_noise_add_f32((float)dx, _lm2_hash_to_f32(_lm2_noise_hash3(cx, cy, cz, 0u)));
        float fy = _lm2_noise_add_f32((float)dy, _lm2_hash_to_f32(_lm2_noise_hash3(cx, cy, cz, 1u)));
        float fz = _lm2_noise_add_f32((float)dz, _lm2_hash_to_f32(_lm2_noise_hash3(cx, cy, cz, 2u)));

        float ddx = _lm2_noise_sub_f32(xf, fx);
        float ddy = _lm2_noise_sub_f32(yf, fy);
        float ddz = _lm2_noise_sub_f32(zf, fz);
        float dist = hypotf(hypotf(ddx, ddy), ddz);

        if (dist < min_dist) {
          min_dist = dist;
        }
      }
    }
  }

  return min_dist;
}
