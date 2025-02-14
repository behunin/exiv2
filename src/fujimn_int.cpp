// SPDX-License-Identifier: GPL-2.0-or-later
/*
  Author(s): Andreas Huggel (ahu) <ahuggel@gmx.net>
             Gilles Caulier (gc) <caulier dot gilles at gmail dot com>
  History:   18-Feb-04, ahu: created
             07-Mar-04, ahu: isolated as a separate component
  Credits:   See header file.
 */
// *****************************************************************************
// included header files
#include "fujimn_int.hpp"
#include "i18n.h"  // NLS support.
#include "tags_int.hpp"
#include "types.hpp"

// + standard includes

// *****************************************************************************
// class member definitions
namespace Exiv2::Internal {
//! OffOn, multiple tags
constexpr TagDetails fujiOffOn[] = {{0, N_("Off")}, {1, N_("On")}};

//! Sharpness, tag 0x1001
constexpr TagDetails fujiSharpness[] = {
    {1, N_("Soft mode 1")}, {2, N_("Soft mode 2")}, {3, N_("Normal")}, {4, N_("Hard mode 1")}, {5, N_("Hard mode 2")}};

//! WhiteBalance, tag 0x1002
constexpr TagDetails fujiWhiteBalance[] = {
    {0, N_("Auto")},
    {256, N_("Daylight")},
    {512, N_("Cloudy")},
    {768, N_("Fluorescent (daylight)")},
    {769, N_("Fluorescent (warm white)")},
    {770, N_("Fluorescent (cool white)")},
    {1024, N_("Incandescent")},
    {3480, N_("Custom")},
    {3480, N_("Custom")}  // To silence compiler warning
};

//! Color, tag 0x1003
constexpr TagDetails fujiColor[] = {
    {0, N_("Normal")},
    {256, N_("High")},
    {512, N_("Low")},
    {768, N_("Monochrome")},
    {769, N_("Monochrome + R Filter")},
    {770, N_("Monochrome + Ye Filter")},
    {771, N_("Monochrome + G Filter")},
    {784, N_("Sepia")},
    {768, N_("Monochrome")}  // To silence compiler warning
};

//! Tone, tag 0x1004
constexpr TagDetails fujiTone[] = {{0, N_("Normal")}, {256, N_("High")}, {512, N_("Low")}};

//! FlashMode, tag 0x1010
constexpr TagDetails fujiFlashMode[] = {
    {0, N_("Auto")},     {1, N_("On")},         {2, N_("Off")},       {3, N_("Red-eye reduction")},
    {4, N_("External")}, {16, N_("Commander")}, {16, N_("Commander")}  // To silence compiler warning
};

//! FocusMode, tag 0x1021
constexpr TagDetails fujiFocusMode[] = {{0, N_("Auto")}, {1, N_("Manual")}};

//! PictureMode, tag 0x1031
constexpr TagDetails fujiPictureMode[] = {{0, N_("Auto")},
                                          {1, N_("Portrait")},
                                          {2, N_("Landscape")},
                                          {4, N_("Sports")},
                                          {5, N_("Night scene")},
                                          {6, N_("Program AE")},
                                          {7, N_("Natural light")},
                                          {8, N_("Anti-blur")},
                                          {10, N_("Sunset")},
                                          {11, N_("Museum")},
                                          {12, N_("Party")},
                                          {13, N_("Flower")},
                                          {14, N_("Text")},
                                          {15, N_("Natural light & flash")},
                                          {16, N_("Beach")},
                                          {17, N_("Snow")},
                                          {18, N_("Fireworks")},
                                          {19, N_("Underwater")},
                                          {256, N_("Aperture-priority AE")},
                                          {512, N_("Shutter speed priority AE")},
                                          {768, N_("Manual")}};

//! ShadowTone, tag 0x1040
//! HighlightTone, tag 0x041
constexpr TagDetails fujiSHTone[] = {
    {-64, N_("+4")}, {-48, N_("+3")}, {-32, N_("+2")}, {-16, N_("+1")}, {0, N_("0")}, {16, N_("-1")}, {32, N_("-2")},
};

//! Continuous, tag 0x1100
constexpr TagDetails fujiContinuous[] = {{0, N_("Off")}, {1, N_("On")}, {2, N_("No flash & flash")}};

//! FinePixColor, tag 0x1210
constexpr TagDetails fujiFinePixColor[] = {{0, N_("Standard")}, {16, N_("Chrome")}, {48, N_("Black & white")}};

//! DynamicRange, tag 0x1400
constexpr TagDetails fujiDynamicRange[] = {{1, N_("Standard")}, {3, N_("Wide")}};

//! FilmMode, tag 0x1401
constexpr TagDetails fujiFilmMode[] = {
    {0, N_("F0/Standard (Provia)")},
    {256, N_("F1/Studio Portrait")},
    {272, N_("F1a/Studio Portrait Enhanced Saturation")},
    {288, N_("F1b/Studio Portrait Smooth Skin Tone (Astia)")},
    {304, N_("F1c/Studio Portrait Increased Sharpness")},
    {512, N_("F2/Fujichrome (Velvia)")},
    {768, N_("F3/Studio Portrait Ex")},
    {1024, N_("F4/Velvia")},
    {1280, N_("Pro Neg. Std")},
    {1281, N_("Pro Neg. Hi")},
    {1536, N_("Classic Chrome")},
};

//! DynamicRange, tag 0x1402
constexpr TagDetails fujiDynamicRangeSetting[] = {{0, N_("Auto (100-400%)")},      {1, N_("Raw")},
                                                  {256, N_("Standard (100%)")},    {512, N_("Wide mode 1 (230%)")},
                                                  {513, N_("Wide mode 2 (400%)")}, {32768, N_("Film simulation mode")}};

//! CropMode, tag 0x104d
constexpr TagDetails fujiCropMode[] = {
    {0, N_("None")},
    {1, N_("Full frame")},
    {2, N_("Sports Finder Mode")},
    {4, N_("Electronic Shutter 1.25x Crop")},
};

//! DRangePriority, tag 0x1443
constexpr TagDetails fujiDRangePriority[] = {{0, N_("Auto")}, {1, N_("Fixed")}};

//! DRangePriorityAuto, tag 0x1444
constexpr TagDetails fujiDRangePriorityAuto[] = {{1, N_("Weak")}, {2, N_("Strong")}};

//! DRangePriorityFixed, tag 0x1445
constexpr TagDetails fujiDRangePriorityFixed[] = {{1, N_("Weak")}, {2, N_("Strong")}};

// Fujifilm MakerNote Tag Info
constexpr TagInfo FujiMakerNote::tagInfo_[] = {
    {0x0000, "Version", N_("Version"), N_("Fujifilm Makernote version"), fujiId, makerTags, undefined, -1, printValue},
    {0x0010, "SerialNumber", N_("Serial Number"),
     N_("This number is unique, and contains the date of manufacture, "
        "but is not the same as the number printed on the camera body."),
     fujiId, makerTags, asciiString, -1, printValue},
    {0x1000, "Quality", N_("Quality"), N_("Image quality setting"), fujiId, makerTags, asciiString, -1, printValue},
    {0x1001, N_("Sharpness"), N_("Sharpness"), N_("Sharpness setting"), fujiId, makerTags, unsignedShort, -1,
     EXV_PRINT_TAG(fujiSharpness)},
    {0x1002, "WhiteBalance", N_("White Balance"), N_("White balance setting"), fujiId, makerTags, unsignedShort, -1,
     EXV_PRINT_TAG(fujiWhiteBalance)},
    {0x1003, "Color", N_("Color"), N_("Chroma saturation setting"), fujiId, makerTags, unsignedShort, -1,
     EXV_PRINT_TAG(fujiColor)},
    {0x1004, "Tone", N_("Tone"), N_("Tone (contrast) setting"), fujiId, makerTags, unsignedShort, -1,
     EXV_PRINT_TAG(fujiTone)},
    {0x1010, "FlashMode", N_("Flash Mode"), N_("Flash firing mode setting"), fujiId, makerTags, unsignedShort, -1,
     EXV_PRINT_TAG(fujiFlashMode)},
    {0x1011, "FlashStrength", N_("Flash Strength"), N_("Flash firing strength compensation setting"), fujiId, makerTags,
     signedRational, -1, printValue},
    {0x1020, "Macro", N_("Macro"), N_("Macro mode setting"), fujiId, makerTags, unsignedShort, -1,
     EXV_PRINT_TAG(fujiOffOn)},
    {0x1021, "FocusMode", N_("Focus Mode"), N_("Focusing mode setting"), fujiId, makerTags, unsignedShort, -1,
     EXV_PRINT_TAG(fujiFocusMode)},
    {0x1022, "0x1022", "0x1022", N_("Unknown"), fujiId, makerTags, unsignedShort, -1, printValue},
    {0x1030, "SlowSync", N_("Slow Sync"), N_("Slow synchro mode setting"), fujiId, makerTags, unsignedShort, -1,
     EXV_PRINT_TAG(fujiOffOn)},
    {0x1031, "PictureMode", N_("Picture Mode"), N_("Picture mode setting"), fujiId, makerTags, unsignedShort, -1,
     EXV_PRINT_TAG(fujiPictureMode)},
    {0x1032, "0x1032", "0x1032", N_("Unknown"), fujiId, makerTags, unsignedShort, -1, printValue},
    {0x1040, "ShadowTone", N_("Shadow Tone"), N_("Shadow tone"), fujiId, makerTags, signedLong, -1,
     EXV_PRINT_TAG(fujiSHTone)},
    {0x1041, "HighlightTone", N_("Highlight Tone"), N_("Highlight tone"), fujiId, makerTags, signedLong, -1,
     EXV_PRINT_TAG(fujiSHTone)},
    {0x104d, "CropMode", N_("Crop Mode"), N_("Crop mode"), fujiId, makerTags, unsignedShort, -1,
     EXV_PRINT_TAG(fujiCropMode)},
    {0x1100, "Continuous", N_("Continuous"), N_("Continuous shooting or auto bracketing setting"), fujiId, makerTags,
     unsignedShort, -1, EXV_PRINT_TAG(fujiContinuous)},
    {0x1101, "SequenceNumber", N_("Sequence Number"), N_("Sequence number"), fujiId, makerTags, unsignedShort, -1,
     printValue},
    {0x1200, "0x1200", "0x1200", N_("Unknown"), fujiId, makerTags, unsignedShort, -1, printValue},
    {0x1210, "FinePixColor", N_("FinePix Color"), N_("Fuji FinePix color setting"), fujiId, makerTags, unsignedShort,
     -1, EXV_PRINT_TAG(fujiFinePixColor)},
    {0x1300, "BlurWarning", N_("Blur Warning"), N_("Blur warning status"), fujiId, makerTags, unsignedShort, -1,
     EXV_PRINT_TAG(fujiOffOn)},
    {0x1301, "FocusWarning", N_("Focus Warning"), N_("Auto Focus warning status"), fujiId, makerTags, unsignedShort, -1,
     EXV_PRINT_TAG(fujiOffOn)},
    {0x1302, "ExposureWarning", N_("Exposure Warning"), N_("Auto exposure warning status"), fujiId, makerTags,
     unsignedShort, -1, EXV_PRINT_TAG(fujiOffOn)},
    {0x1400, "DynamicRange", N_("Dynamic Range"), N_("Dynamic range"), fujiId, makerTags, unsignedShort, -1,
     EXV_PRINT_TAG(fujiDynamicRange)},
    {0x1401, "FilmMode", N_("Film Mode"), N_("Film mode"), fujiId, makerTags, unsignedShort, -1,
     EXV_PRINT_TAG(fujiFilmMode)},
    {0x1402, "DynamicRangeSetting", N_("Dynamic Range Setting"), N_("Dynamic range settings"), fujiId, makerTags,
     unsignedShort, -1, EXV_PRINT_TAG(fujiDynamicRangeSetting)},
    {0x1403, "DevelopmentDynamicRange", N_("Development Dynamic Range"), N_("Development dynamic range"), fujiId,
     makerTags, unsignedShort, -1, printValue},
    {0x1404, "MinFocalLength", N_("Minimum Focal Length"), N_("Minimum focal length"), fujiId, makerTags,
     unsignedRational, -1, printValue},
    {0x1405, "MaxFocalLength", N_("Maximum Focal Length"), N_("Maximum focal length"), fujiId, makerTags,
     unsignedRational, -1, printValue},
    {0x1406, "MaxApertureAtMinFocal", N_("Maximum Aperture at Minimum Focal"), N_("Maximum aperture at minimum focal"),
     fujiId, makerTags, unsignedRational, -1, printValue},
    {0x1407, "MaxApertureAtMaxFocal", N_("Maximum Aperture at Maximum Focal"), N_("Maximum aperture at maximum focal"),
     fujiId, makerTags, unsignedRational, -1, printValue},
    {0x1431, "Rating", N_("Rating"), N_("Rating"), fujiId, makerTags, unsignedLong, -1, printValue},
    {0x1443, "DRangePriority", N_("D Range Priority"), N_("Dynamic range priority"), fujiId, makerTags, unsignedShort,
     -1, EXV_PRINT_TAG(fujiDRangePriority)},
    {0x1444, "DRangePriorityFixed", N_("D Range Priority Fixed"), N_("Dynamic range priority fixed"), fujiId, makerTags,
     unsignedShort, -1, EXV_PRINT_TAG(fujiDRangePriorityFixed)},
    {0x1445, "DRangePriorityAuto", N_("D Range Priority Auto"), N_("Dynamic range priority auto"), fujiId, makerTags,
     unsignedShort, -1, EXV_PRINT_TAG(fujiDRangePriorityAuto)},
    {0x8000, "FileSource", N_("File Source"), N_("File source"), fujiId, makerTags, asciiString, -1, printValue},
    {0x8002, "OrderNumber", N_("Order Number"), N_("Order number"), fujiId, makerTags, unsignedLong, -1, printValue},
    {0x8003, "FrameNumber", N_("Frame Number"), N_("Frame number"), fujiId, makerTags, unsignedShort, -1, printValue},
    // #1402
    {0xf000, "FujiIFD", N_("FujiIFD"), N_("Fujifilm IFD"), fujiId, makerTags, undefined, -1, printValue},
    {0xf001, "RawImageFullWidth", N_("Raw Image Full Width"), N_("Raw Image Full Width"), fujiId, makerTags, undefined,
     -1, printValue},
    {0xf002, "RawImageFullHeight", N_("Raw Image Full Height"), N_("Raw Image Full Height"), fujiId, makerTags,
     undefined, -1, printValue},
    {0xf003, "BitsPerSample", N_("Bits Per Sample"), N_("Bits Per Sample"), fujiId, makerTags, undefined, -1,
     printValue},
    {0xf007, "StripOffsets", N_("Strip Offsets"), N_("Strip Offsets"), fujiId, makerTags, undefined, -1, printValue},
    {0xf008, "StripByteCounts", N_("Strip Byte Counts"), N_("Strip Byte Counts"), fujiId, makerTags, undefined, -1,
     printValue},
    {0xf00a, "BlackLevel", N_("Black Level"), N_("Black Level"), fujiId, makerTags, undefined, -1, printValue},
    {0xf00b, "GeometricDistortionParams", N_("Geometric Distortion Params"), N_("Geometric Distortion Params"), fujiId,
     makerTags, undefined, -1, printValue},
    {0xf00c, "WB_GRBLevelsStandard", N_("WB GRB Levels Standard"), N_("WB GRB Levels Standard"), fujiId, makerTags,
     undefined, -1, printValue},
    {0xf00d, "WB_GRBLevelsAuto", N_("WB GRB Levels Auto"), N_("WB GRB Levels Auto"), fujiId, makerTags, undefined, -1,
     printValue},
    {0xf00e, "WB_GRBLevels", N_("WB GRB Levels"), N_("WB GRB Levels"), fujiId, makerTags, undefined, -1, printValue},
    {0xf00f, "ChromaticAberrationParams", N_("Chromatic Aberration Params"), N_("Chromatic Aberration Params"), fujiId,
     makerTags, undefined, -1, printValue},
    {0xf010, "VignettingParams", N_("Vignetting Params"), N_("Vignetting Params"), fujiId, makerTags, undefined, -1,
     printValue},

    // End of list marker
    {0xffff, "(UnknownFujiMakerNoteTag)", "(UnknownFujiMakerNoteTag)", N_("Unknown FujiMakerNote tag"), fujiId,
     makerTags, asciiString, -1, printValue},
};

const TagInfo* FujiMakerNote::tagList() {
  return tagInfo_;
}

}  // namespace Exiv2::Internal
