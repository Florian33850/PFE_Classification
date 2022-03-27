//     PFE_Classification --- Generic classification software
//     Copyright © <2022> Florian Dayre <florian.dayre33850@gmail.com>
//     Copyright © <2022> Élodie Gaudry <elodie.gaudry@etu.u-bordeaux.fr>
//     Copyright © <2022> Hugo Lecomte <hugolecomte932@protonmail.com>
//     Copyright © <2022> Hugo Trarieux <htrarieux@gmail.com>

//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     any later version.

//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.

//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef CONSTANTS_H
#define CONSTANTS_H

//      ---     GENERAL CONSTANTS      ---

#define OUTPUT_TRAINING_FILE_NAME "outputTraining.txt"
#define ERROR_OUTPUT_TRAINING_FILE_NAME "errorOutputTraining.txt"
#define OUTPUT_RESULT_FILE_NAME "outputResult.txt"
#define ERROR_OUTPUT_RESULT_FILE_NAME "errorOutputResult.txt"

#define QPROCESS_NO_TIME_OUT -1

#define COMMAND_RUNNER "python3"

#define QINT_VALIDATOR_MIN 0

#define FIRST_WIDGET_INDEX 0

#define QSTRINGS_ARE_EQUALS 0

//      ===     WIDGETS     ===
//      ---     Mirror Transformation     ---
#define ROW_MIRROR_WIDGET_TITLE 0
#define COLUMN_MIRROR_WIDGET_TITLE 0
#define ROW_SPAN_MIRROR_WIDGET_TITLE 1
#define COLUMN_SPAN_MIRROR_WIDGET_TITLE 1

#define ROW_HORIZONTAL_CHECK_BOX 1
#define COLUMN_HORIZONTAL_CHECK_BOX 0
#define ROW_SPAN_HORIZONTAL_CHECK_BOX 2
#define COLUMN_SPAN_HORIZONTAL_CHECK_BOX 1

#define ROW_VERTICAL_CHECK_BOX 2
#define COLUMN_VERTICAL_CHECK_BOX 0
#define ROW_SPAN_VERTICAL_CHECK_BOX 2
#define COLUMN_SPAN_VERTICAL_CHECK_BOX 1

#define ROW_DELETE_WIDGET_BUTTON 0
#define COLUMN_DELETE_WIDGET_BUTTON 1
#define ROW_SPAN_DELETE_WIDGET_BUTTON 1
#define COLUMN_SPAN_DELETE_WIDGET_BUTTON 1

//      ---     Morphological Transformation      ---
#define MORPHOLOGICAL_TRANSFORMATION_MINIMUM_KERNEL_SIZE 1
#define MORPHOLOGICAL_TRANSFORMATION_MAXIMUM_KERNEL_SIZE 20

#define MORPHOLOGICAL_TRANSFORMATION_MINIMUM_NUMBER_ITERATION 1
#define MORPHOLOGICAL_TRANSFORMATION_MAXIMUM_NUMBER_ITERATION 10

#define ROW_MORPHOLOGICAL_TRANSFORMATION_WIDGET_TITLE 0
#define COLUMN_MORPHOLOGICAL_TRANSFORMATION_WIDGET_TITLE 0

#define ROW_MORPHOLOGICAL_TRANSFORMATION_TYPE 1
#define COLUMN_MORPHOLOGICAL_TRANSFORMATION_TYPE 0

#define ROW_MORPHOLOGICAL_TRANSFORMATION_KERNEL_SIZE_SLIDER 2
#define COLUMN_MORPHOLOGICAL_TRANSFORMATION_KERNEL_SIZE_SLIDER 0

#define ROW_MORPHOLOGICAL_TRANSFORMATION_NUMBER_ITERATION 3
#define COLUMN_MORPHOLOGICAL_TRANSFORMATION_NUMBER_ITERATION 0

#define ROW_MORPHOLOGICAL_TRANSFORMATION_DELETE_WIDGET_BUTTON 0
#define COLUMN_MORPHOLOGICAL_TRANSFORMATION_DELETE_WIDGET_BUTTON 1

//      ---     Data Handler      ---

#define MAX_NUMBER_OF_IMAGES_TO_LOAD_DATA_HANDLER_IMAGESELECTION 10
#define MAX_NUMBER_OF_IMAGES_TO_LOAD_DATA_HANDLER_LYMEDATABASE 10

//      ---     Image Label      ---

#define MINIMUM_IMAGE_WIDTH_IMAGE_LABEL 100
#define MINIMUM_IMAGE_HEIGHT_IMAGE_LABEL 100

//      ---     Image Transformation Viewer      ---

#define MAIN_LAYOUT_MARGIN_IMAGE_TRANSFORMATION_VIEWER 1
#define MAIN_LAYOUT_SPACING_IMAGE_TRANSFORMATION_VIEWER 1

//      ---     Image Transformation      ---

#define AUTOMATIC_ROTATION_IMAGE_TRANSFORMATION_MAX_DILATATION_SIZE 20;

//      ---     Image Preview      ---

#define IMAGES_PREVIEW_MAXIMUM_ROWS 2
#define IMAGES_PREVIEW_MAXIMUM_COLLUMNS 5
#define IMAGES_PREVIEW_MAIN_LAYOUT_SPACING 1
#define IMAGES_PREVIEW_MAIN_LAYOUT_MARGIN 1
#define ROW_IMAGES_PREVIEW_IMAGES_LAYOUT 0
#define COLUMN_IMAGES_PREVIEW_IMAGES_LAYOUT 0
#define ROW_SPAN_IMAGES_PREVIEW_IMAGES_LAYOUT 3
#define COLUMN_SPAN_IMAGES_PREVIEW_IMAGES_LAYOUT 3

#define ROW_IMAGES_PREVIEW_PREVIOUS_BUTTON 3
#define COLUMN_IMAGES_PREVIEW_PREVIOUS_BUTTON 0
#define ROW_SPAN_IMAGES_PREVIEW_PREVIOUS_BUTTON 1
#define COLUMN_SPAN_IMAGES_PREVIEW_PREVIOUS_BUTTON 1

#define ROW_IMAGES_PREVIEW_NEXT_BUTTON 3
#define COLUMN_IMAGES_PREVIEW_NEXT_BUTTON 2
#define ROW_SPAN_IMAGES_PREVIEW_NEXT_BUTTON 1
#define COLUMN_SPAN_IMAGES_PREVIEW_NEXT_BUTTON 1

//      ---     Tab       ---

#define TAB_MAIN_LAYOUT_SPACING 1
#define TAB_MAIN_LAYOUT_MARGIN 1

//      ---     Preprocessing Tab       ---

#define ROW_PREPROCESSING_TAB_PREVIEW_WIDGET 0
#define COLUMN_PREPROCESSING_TAB_PREVIEW_WIDGET 0
#define ROW_SPAN_PREPROCESSING_TAB_PREVIEW_WIDGET 3
#define COLUMN_SPAN_PREPROCESSING_TAB_PREVIEW_WIDGET 3

#define ROW_PREPROCESSING_TAB_TRANSFORMATION_VIEWER 0
#define COLUMN_PREPROCESSING_TAB_TRANSFORMATION_VIEWER 3
#define ROW_SPAN_PREPROCESSING_TAB_TRANSFORMATION_VIEWER 3
#define COLUMN_SPAN_PREPROCESSING_TAB_TRANSFORMATION_VIEWER 1

#define ROW_PREPROCESSING_TAB_SAVE_BUTTON 2
#define COLUMN_PREPROCESSING_TAB_SAVE_BUTTON 3
#define ROW_SPAN_PREPROCESSING_TAB_SAVE_BUTTON 1
#define COLUMN_SPAN_PREPROCESSING_TAB_SAVE_BUTTON 1

//      ---     Result Tab       ---

#define ROW_RESULT_TAB_CLASSIFICATION_PARAMETERS_LAYOUT 0
#define COLUMN_RESULT_TAB_CLASSIFICATION_PARAMETERS_LAYOUT 0

#define ROW_RESULT_TAB_RESULT_OUTPUT_LAYOUT 1
#define COLUMN_RESULT_TAB_RESULT_OUTPUT_LAYOUT 0

//      ---     Classification Training Tab       ---

#define ROW_CLASSIFICATION_TRAINING_TAB_COMBO_BOX 0
#define COLUMN_CLASSIFICATION_TRAINING_TAB_COMBO_BOX 0
#define ROW_CLASSIFICATION_TRAINING_TAB_PARAMETERS_LAYOUT 1
#define COLUMN_CLASSIFICATION_TRAINING_TAB_PARAMETERS_LAYOUT 0
#define ROW_CLASSIFICATION_TRAINING_TAB_TRAINING_OUTPUT_LAYOUT 2
#define COLUMN_CLASSIFICATION_TRAINING_TAB_TRAINING_OUTPUT_LAYOUT 0

//      ---     Data Augmentation Tab       ---

#define ROW_DATA_AUGMENTATION_TAB_IMAGES_PREVIEW_WIDGET 0
#define COLUMN_DATA_AUGMENTATION_TAB_IMAGES_PREVIEW_WIDGET 0
#define ROW_SPAN_DATA_AUGMENTATION_TAB_IMAGES_PREVIEW_WIDGET 3
#define COLUMN_SPAN_DATA_AUGMENTATION_TAB_IMAGES_PREVIEW_WIDGET 3

#define ROW_DATA_AUGMENTATION_TAB_TRANSFORMATION_VIEWER 0
#define COLUMN_DATA_AUGMENTATION_TAB_TRANSFORMATION_VIEWER 3
#define ROW_SPAN_DATA_AUGMENTATION_TAB_TRANSFORMATION_VIEWER 3
#define COLUMN_SPAN_DATA_AUGMENTATION_TAB_TRANSFORMATION_VIEWER 1

#define ROW_DATA_AUGMENTATION_TAB_SAVE_IMAGES_BUTTON 3
#define COLUMN_DATA_AUGMENTATION_TAB_SAVE_IMAGES_BUTTON 3
#define ROW_SPAN_DATA_AUGMENTATION_TAB_SAVE_IMAGES_BUTTON 1
#define COLUMN_SPAN_DATA_AUGMENTATION_TAB_SAVE_IMAGES_BUTTON 1

#define ROW_DATA_AUGMENTATION_TAB_DATABASE_COUNT_LAYOUT 3
#define COLUMN_DATA_AUGMENTATION_TAB_DATABASE_COUNT_LAYOUT 0
#define ROW_SPAN_DATA_AUGMENTATION_TAB_DATABASE_COUNT_LAYOUT 1
#define COLUMN_SPAN_DATA_AUGMENTATION_TAB_DATABASE_COUNT_LAYOUT 3

#endif // CONSTANTS_H
