#include "model/model.h"

// .6 fixed-point
struct vertex_position majora_position[] = {
  {28, 13, -2},
  {41, -9, -3},
  {17, 4, -2},
  {23, 8, 2},
  {-24, 8, 2},
  {-29, 13, -2},
  {-42, -9, -3},
  {-18, 4, -2},
  {0, 61, -3},
  {41, 20, -5},
  {0, -13, -7},
  {16, 68, -3},
  {35, 68, -3},
  {49, 52, -3},
  {-49, 52, -3},
  {-36, 68, -3},
  {-17, 68, -3},
  {-42, 20, -5},
  {-28, 95, 0},
  {-16, 63, -1},
  {-31, 62, -1},
  {-23, 60, 6},
  {22, 60, 6},
  {30, 62, -1},
  {27, 95, 0},
  {15, 63, -1},
  {64, 20, -1},
  {36, 25, -1},
  {43, 36, -1},
  {39, 30, 3},
  {-40, 30, 3},
  {-44, 36, -1},
  {-65, 20, -1},
  {-37, 25, -1},
  {-4, -4, -3},
  {-25, -20, -3},
  {-18, 3, -2},
  {-11, -1, 1},
  {24, -20, -3},
  {17, 3, -2},
  {10, -1, 1},
  {3, -4, -3},
  {-28, 14, -2},
  {-54, 3, -2},
  {-38, 23, -1},
  {-33, 18, 2},
  {53, 3, -2},
  {37, 23, -1},
  {32, 18, 2},
  {27, 14, -2},
  {0, 61, -3},
  {0, 42, 13},
  {6, 54, 11},
  {15, 29, 17},
  {0, 13, 6},
  {-16, 29, 17},
  {-19, 45, 18},
  {0, -13, -7},
  {-12, 14, 15},
  {-17, 68, -3},
  {-13, 61, 7},
  {-36, 68, -3},
  {-49, 52, -3},
  {-37, 48, 14},
  {-14, 53, 17},
  {-7, 54, 11},
  {30, 24, 13},
  {41, 20, -5},
  {49, 52, -3},
  {13, 53, 17},
  {18, 45, 18},
  {-31, 24, 13},
  {-42, 20, -5},
  {-24, 14, 7},
  {23, 14, 7},
  {-27, 60, 11},
  {12, 61, 7},
  {16, 68, -3},
  {26, 60, 11},
  {35, 68, -3},
  {36, 48, 14},
  {11, 14, 15},
};

// .14 fixed-point
struct vertex_texture majora_texture[] = {
  {11583, 9984},
  {13855, 16384},
  {16352, 31},
  {12704, 13184},
  {0, 31},
  {3647, 13184},
  {2496, 16384},
  {4768, 9984},
  {16223, 0},
  {16384, 16288},
  {3072, 3664},
  {256, 11056},
  {5439, 16415},
  {1679, 15952},
  {5456, 16384},
  {0, 384},
  {672, 16384},
  {4096, 1055},
  {2111, 0},
  {15679, 16384},
  {14240, 0},
  {16352, 384},
  {12256, 1055},
  {13631, 16384},
  {16384, 0},
  {12768, 4768},
  {13184, 10591},
  {0, 0},
  {3167, 10591},
  {2720, 16384},
  {3584, 4768},
  {2399, 16384},
  {6880, 11968},
  {0, 0},
  {4639, 14175},
  {11712, 14175},
  {16384, 0},
  {13951, 16384},
  {9472, 11968},
  {2399, 16384},
  {3968, 8735},
  {0, 0},
  {3167, 12575},
  {13184, 12575},
  {16384, 0},
  {13951, 16384},
  {12383, 8735},
  {10944, 13767},
  {12256, 16384},
  {12256, 11080},
  {12263, 5359},
  {8623, 8960},
  {8192, 12544},
  {8647, 5407},
  {12263, -17},
  {8840, 15552},
  {6792, 16415},
  {4415, 12712},
  {4112, 16440},
  {2976, 13160},
  {9232, 13943},
  {5744, 7960},
  {4112, 4903},
  {6431, 4712},
  {11480, -17},
  {6999, 15016},
};

// .9 fixed-point
struct vertex_normal majora_normal[] = {
  {-233, -430, -155},
  {425, 262, -113},
  {107, -155, 476},
  {48, -84, 502},
  {-108, -155, 476},
  {-49, -84, 502},
  {-426, 262, -113},
  {-426, 262, -113},
  {232, -430, -155},
  {232, -430, -155},
  {48, -84, 502},
  {107, -155, 476},
  {0, 25, -512},
  {0, 25, -512},
  {0, 25, -512},
  {0, 25, -512},
  {0, 25, -512},
  {-1, 25, -512},
  {-1, 25, -512},
  {-1, 25, -512},
  {0, 25, -512},
  {0, 25, -512},
  {0, 25, -512},
  {0, 25, -512},
  {-1, 25, -512},
  {-1, 25, -512},
  {-1, 25, -512},
  {-1, 25, -512},
  {-478, 46, -181},
  {-27, 245, 448},
  {444, 184, -176},
  {-12, 75, 506},
  {444, 184, -176},
  {26, 245, 448},
  {11, 75, 506},
  {477, 46, -181},
  {26, 245, 448},
  {477, 46, -181},
  {-445, 184, -176},
  {-445, 184, -176},
  {11, 75, 506},
  {-12, 75, 506},
  {-27, 245, 448},
  {-478, 46, -181},
  {291, 405, -113},
  {142, -104, 480},
  {-79, -479, -165},
  {62, -61, 504},
  {-79, -479, -165},
  {142, -104, 480},
  {-143, -104, 480},
  {-63, -61, 504},
  {-292, 405, -113},
  {-292, 405, -113},
  {78, -479, -165},
  {-143, -104, 480},
  {78, -479, -165},
  {142, -104, 480},
  {291, 405, -113},
  {-475, 155, -112},
  {312, -378, -149},
  {-80, -177, 473},
  {312, -378, -148},
  {-37, -96, 501},
  {-80, -177, 473},
  {36, -96, 501},
  {79, -177, 473},
  {474, 155, -112},
  {-313, -378, -149},
  {474, 155, -112},
  {79, -177, 473},
  {36, -96, 501},
  {-313, -378, -148},
  {-475, 155, -112},
  {-391, 311, -113},
  {187, -450, -159},
  {-121, -143, 476},
  {187, -450, -159},
  {-54, -78, 503},
  {-121, -143, 476},
  {53, -78, 503},
  {120, -143, 476},
  {390, 311, -113},
  {-188, -450, -159},
  {390, 311, -113},
  {120, -143, 476},
  {53, -78, 503},
  {-188, -450, -159},
  {120, -143, 476},
  {-121, -143, 476},
  {-54, -78, 503},
  {-391, 311, -113},
  {-276, 297, 311},
  {0, 398, 321},
  {0, 75, 506},
  {0, -109, 500},
  {-48, -49, 507},
  {0, 74, 506},
  {-26, 46, 509},
  {47, -49, 507},
  {13, -212, 466},
  {0, -355, 369},
  {-1, -109, 500},
  {157, 391, 290},
  {0, 398, 321},
  {85, 425, 271},
  {-243, 93, 441},
  {-211, 346, 312},
  {-417, 7, 297},
  {275, 297, 311},
  {117, 241, 435},
  {416, 7, 297},
  {283, -182, 385},
  {347, -277, 254},
  {-118, 241, 435},
  {25, 46, 509},
  {-252, -339, 290},
  {-284, -182, 385},
  {-348, -277, 254},
  {251, -339, 290},
  {347, -278, 254},
  {-64, 330, 385},
  {85, 425, 271},
  {-211, 346, 312},
  {-26, 46, 509},
  {-417, 7, 297},
  {-348, -277, 254},
  {-158, 391, 290},
  {-86, 425, 271},
  {-86, 425, 271},
  {63, 330, 385},
  {210, 346, 312},
  {210, 346, 312},
  {242, 93, 441},
  {416, 7, 297},
  {25, 46, 509},
  {-1, 74, 506},
  {283, -182, 385},
  {347, -277, 254},
  {0, -355, 369},
  {-348, -278, 254},
  {-14, -212, 466},
  {0, -109, 500},
  {157, 391, 290},
  {275, 297, 311},
  {117, 241, 435},
  {-64, 330, 385},
  {-26, 46, 509},
  {-243, 93, 441},
  {47, -49, 507},
  {-252, -339, 290},
  {-158, 391, 290},
  {-276, 297, 311},
  {25, 46, 509},
  {63, 330, 385},
  {-118, 241, 435},
  {-48, -49, 507},
  {242, 93, 441},
  {-48, -49, 507},
  {251, -339, 290},
  {117, 241, 435},
  {-64, 330, 385},
  {-118, 241, 435},
  {63, 330, 385},
  {-243, 93, 441},
  {210, 346, 312},
  {63, 330, 385},
  {-284, -182, 385},
  {416, 7, 297},
  {13, -212, 466},
  {-14, -212, 466},
};

struct triangle majora_1_triangle[] = {
  {
    {2, 0, 0},
    {0, 1, 1},
    {1, 2, 2},
  },
  {
    {3, 3, 3},
    {2, 0, 0},
    {1, 2, 2},
  },
  {
    {6, 4, 4},
    {4, 5, 5},
    {5, 6, 6},
  },
  {
    {5, 6, 7},
    {7, 7, 8},
    {6, 4, 4},
  },
  {
    {7, 7, 9},
    {4, 5, 5},
    {6, 4, 4},
  },
  {
    {3, 3, 10},
    {1, 2, 11},
    {0, 1, 1},
  },
};

struct object majora_1 = {
  .triangle = &majora_1_triangle[0],
  .quadrilateral = NULL,
  .triangle_count = 6,
  .quadrilateral_count = 0,
  .material = mtl_06007BE0,
};

struct triangle majora_3_triangle[] = {
  {
    {10, 8, 12},
    {8, 9, 13},
    {9, 10, 14},
  },
  {
    {13, 11, 15},
    {11, 12, 15},
    {12, 13, 16},
  },
  {
    {16, 14, 17},
    {14, 11, 17},
    {15, 13, 18},
  },
  {
    {14, 11, 19},
    {8, 9, 19},
    {17, 10, 19},
  },
  {
    {8, 9, 20},
    {13, 11, 20},
    {9, 10, 20},
  },
  {
    {11, 12, 21},
    {13, 11, 22},
    {8, 9, 23},
  },
  {
    {14, 11, 24},
    {16, 14, 25},
    {8, 9, 23},
  },
  {
    {8, 9, 26},
    {10, 8, 12},
    {17, 10, 27},
  },
};

struct object majora_3 = {
  .triangle = &majora_3_triangle[0],
  .quadrilateral = NULL,
  .triangle_count = 8,
  .quadrilateral_count = 0,
  .material = mtl_06007FE0,
};

struct triangle majora_4_triangle[] = {
  {
    {20, 15, 28},
    {18, 16, 29},
    {19, 17, 30},
  },
  {
    {21, 18, 31},
    {19, 17, 32},
    {18, 16, 29},
  },
  {
    {24, 19, 33},
    {22, 20, 34},
    {23, 21, 35},
  },
  {
    {24, 19, 36},
    {23, 21, 37},
    {25, 22, 38},
  },
  {
    {25, 22, 39},
    {22, 20, 40},
    {24, 19, 36},
  },
  {
    {21, 18, 41},
    {18, 16, 42},
    {20, 15, 43},
  },
  {
    {28, 23, 44},
    {26, 24, 45},
    {27, 25, 46},
  },
  {
    {29, 26, 47},
    {27, 25, 48},
    {26, 24, 49},
  },
  {
    {32, 27, 50},
    {30, 28, 51},
    {31, 29, 52},
  },
  {
    {31, 29, 53},
    {33, 30, 54},
    {32, 27, 55},
  },
  {
    {33, 30, 56},
    {30, 28, 51},
    {32, 27, 50},
  },
  {
    {29, 26, 47},
    {26, 24, 57},
    {28, 23, 58},
  },
};

struct object majora_4 = {
  .triangle = &majora_4_triangle[0],
  .quadrilateral = NULL,
  .triangle_count = 12,
  .quadrilateral_count = 0,
  .material = mtl_060077E0,
};

struct triangle majora_5_triangle[] = {
  {
    {36, 31, 59},
    {34, 32, 60},
    {35, 33, 61},
  },
  {
    {34, 32, 62},
    {37, 34, 63},
    {35, 33, 64},
  },
  {
    {40, 35, 65},
    {38, 36, 66},
    {39, 37, 67},
  },
  {
    {41, 38, 68},
    {39, 37, 69},
    {38, 36, 70},
  },
  {
    {40, 35, 71},
    {41, 38, 72},
    {38, 36, 66},
  },
  {
    {35, 33, 64},
    {37, 34, 63},
    {36, 31, 73},
  },
};

struct object majora_5 = {
  .triangle = &majora_5_triangle[0],
  .quadrilateral = NULL,
  .triangle_count = 6,
  .quadrilateral_count = 0,
  .material = mtl_06007DE0,
};

struct triangle majora_6_triangle[] = {
  {
    {44, 39, 74},
    {42, 40, 75},
    {43, 41, 76},
  },
  {
    {42, 40, 77},
    {45, 42, 78},
    {43, 41, 79},
  },
  {
    {48, 43, 80},
    {46, 44, 81},
    {47, 45, 82},
  },
  {
    {49, 46, 83},
    {47, 45, 84},
    {46, 44, 85},
  },
  {
    {48, 43, 86},
    {49, 46, 87},
    {46, 44, 88},
  },
  {
    {43, 41, 89},
    {45, 42, 90},
    {44, 39, 91},
  },
};

struct object majora_6 = {
  .triangle = &majora_6_triangle[0],
  .quadrilateral = NULL,
  .triangle_count = 6,
  .quadrilateral_count = 0,
  .material = mtl_060079E0,
};

struct triangle majora_7_triangle[] = {
  {
    {52, 47, 92},
    {50, 48, 93},
    {51, 49, 94},
  },
  {
    {54, 50, 95},
    {53, 51, 96},
    {51, 49, 97},
  },
  {
    {56, 52, 98},
    {55, 51, 99},
    {51, 49, 97},
  },
  {
    {58, 53, 100},
    {57, 54, 101},
    {54, 50, 102},
  },
  {
    {60, 55, 103},
    {50, 48, 104},
    {59, 56, 105},
  },
  {
    {63, 57, 106},
    {61, 58, 107},
    {62, 59, 108},
  },
  {
    {65, 47, 109},
    {64, 60, 110},
    {51, 49, 97},
  },
  {
    {68, 59, 111},
    {66, 61, 112},
    {67, 62, 113},
  },
  {
    {69, 60, 114},
    {52, 47, 92},
    {51, 49, 97},
  },
  {
    {70, 52, 115},
    {69, 60, 114},
    {51, 49, 97},
  },
  {
    {73, 63, 116},
    {71, 61, 117},
    {72, 62, 118},
  },
  {
    {74, 63, 119},
    {57, 64, 101},
    {67, 62, 120},
  },
  {
    {50, 48, 93},
    {65, 47, 109},
    {51, 49, 97},
  },
  {
    {75, 65, 121},
    {59, 56, 122},
    {61, 58, 123},
  },
  {
    {64, 60, 110},
    {56, 52, 124},
    {51, 49, 97},
  },
  {
    {71, 61, 117},
    {62, 59, 125},
    {72, 62, 126},
  },
  {
    {55, 51, 99},
    {54, 50, 95},
    {51, 49, 97},
  },
  {
    {50, 48, 104},
    {76, 55, 127},
    {77, 56, 128},
  },
  {
    {77, 56, 129},
    {78, 65, 130},
    {79, 58, 131},
  },
  {
    {79, 58, 132},
    {80, 57, 133},
    {68, 59, 134},
  },
  {
    {53, 51, 96},
    {70, 52, 135},
    {51, 49, 136},
  },
  {
    {66, 61, 137},
    {74, 63, 119},
    {67, 62, 138},
  },
  {
    {57, 64, 139},
    {73, 63, 116},
    {72, 62, 140},
  },
  {
    {57, 54, 101},
    {81, 53, 141},
    {54, 50, 142},
  },
  {
    {50, 48, 104},
    {60, 55, 143},
    {65, 47, 144},
  },
  {
    {60, 55, 143},
    {64, 60, 145},
    {65, 47, 144},
  },
  {
    {75, 65, 146},
    {56, 52, 147},
    {64, 60, 110},
  },
  {
    {63, 57, 148},
    {55, 51, 149},
    {56, 52, 124},
  },
  {
    {71, 61, 117},
    {58, 53, 100},
    {55, 51, 149},
  },
  {
    {73, 63, 150},
    {57, 54, 101},
    {58, 53, 100},
  },
  {
    {76, 55, 151},
    {50, 48, 93},
    {52, 47, 152},
  },
  {
    {69, 60, 114},
    {76, 55, 151},
    {52, 47, 152},
  },
  {
    {70, 52, 153},
    {78, 65, 154},
    {69, 60, 155},
  },
  {
    {53, 51, 156},
    {80, 57, 157},
    {70, 52, 115},
  },
  {
    {81, 53, 141},
    {66, 61, 137},
    {53, 51, 158},
  },
  {
    {57, 54, 101},
    {74, 63, 159},
    {81, 53, 141},
  },
  {
    {64, 60, 160},
    {60, 55, 103},
    {75, 65, 161},
  },
  {
    {76, 55, 127},
    {69, 60, 162},
    {78, 65, 130},
  },
  {
    {59, 56, 105},
    {75, 65, 121},
    {60, 55, 103},
  },
  {
    {78, 65, 163},
    {77, 56, 128},
    {76, 55, 127},
  },
  {
    {56, 52, 147},
    {75, 65, 146},
    {63, 57, 164},
  },
  {
    {61, 58, 123},
    {63, 57, 164},
    {75, 65, 121},
  },
  {
    {78, 65, 154},
    {70, 52, 153},
    {80, 57, 133},
  },
  {
    {80, 57, 133},
    {79, 58, 165},
    {78, 65, 166},
  },
  {
    {55, 51, 149},
    {63, 57, 164},
    {71, 61, 167},
  },
  {
    {80, 57, 133},
    {53, 51, 158},
    {66, 61, 137},
  },
  {
    {62, 59, 125},
    {71, 61, 167},
    {63, 57, 164},
  },
  {
    {66, 61, 112},
    {68, 59, 168},
    {80, 57, 133},
  },
  {
    {54, 50, 95},
    {55, 51, 149},
    {58, 53, 169},
  },
  {
    {53, 51, 158},
    {54, 50, 95},
    {81, 53, 170},
  },
  {
    {58, 53, 100},
    {71, 61, 117},
    {73, 63, 150},
  },
  {
    {66, 61, 137},
    {81, 53, 170},
    {74, 63, 159},
  },
};

struct object majora_7 = {
  .triangle = &majora_7_triangle[0],
  .quadrilateral = NULL,
  .triangle_count = 52,
  .quadrilateral_count = 0,
  .material = mtl_060067E0,
};

