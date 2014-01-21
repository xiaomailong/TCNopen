﻿/******************************************************************************/
/**
 * @file            parsebody.h
 *
 * @brief           Loading of the XML description
 *
 * @details
 *
 * @note            Project: TRDP SPY
 *
 * @author          Florian Weispfenning, Bombardier Transportation
 *
 * @remarks This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 *          If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *          Copyright Bombardier Transportation Inc. or its subsidiaries and others, 2013. All rights reserved.
 *
 * $Id$
 *
 */

#ifndef TRDP_PARESEBODY_H
#define TRDP_PARESEBODY_H

/*******************************************************************************
 * INCLUDES
 */
#include <string.h>
#include <glib.h>

/*******************************************************************************
 * DEFINES
 */


/*******************************************************************************
 * TYPEDEFS
 */

/** @struct ComId
 *
 @dot
digraph Reference {
node [shape=record, fontname=Helvetica];
c [ label="ComId" ];
d [ label="Dataset" ];
e [ label="Element" ];
c -> d [ ];
d -> d [ ];
d -> e [ ];
}
@enddot
 *
 *
 *  @brief This struct makes a mapping between one comId and one dataset.
 *
 *  This is a separate structure, because there could be mappings from a dataset to another one.
 */
struct ComId {
	guint32 comId;      /**< Communication Id, used as key*/
	guint datasetId;    /**< Id for a dataset ( @link #Dataset see Dataset structure @endlink) */
};

/** @struct Dataset
 *  @brief Description of one dataset.
 */
struct Dataset {
    guint datasetId;        /**< Unique identification of one dataset */
	GString *name;          /**< Description of the dataset */
	GSList *listOfElements; /**< All elements, this dataset consists of. */
};

/** @struct Element
 *  @brief description of one element, with a variable that is stored
 *  @var Element::name
 *  Name of the variable, that is stored
 *  @var Element::type
 *  Numeric type of the variable (see Usermanual, chapter 4.2)
 *  @var Element::array_size
 *  Amount this value occured. 1 is default; 0 indicates a dynamic list (the dynamic list starts with a 16bit value with the occurence)
 *  @var Element::unit
 *  Unit to display
 *  @var Element::scale
 *  A factor the given value is scaled
 *  @var Element::offset
 *  Offset that is added to the values. displayed value = scale * raw value + offset
 */
struct Element {
	GString* 	name;
	guint32 	type;
	GString* 	typeName;
	guint32 array_size;
	GString* 	unit;
	gfloat 	scale;
	gint32 offset;
};

enum TRDP_RET {
	TRDP_PARSEBODY_OK = 0,
	TRDP_PARSEBODY_ERR,
	TRDP_PARSEBODY_ERR_IO_ERROR,
	TRDP_PARSEBODY_ERR_PARSE_XML,
	TRDP_PARSEBODY_ERR_FILE_NOT_FOUND,
};

typedef enum TRDP_RET TRDP_RET_t;

/*******************************************************************************
 * GLOBAL FUNCTIONS
 */


/** @fn TRDP_RET_t trdp_parsebody_init(const char ** xmlconfigFile)
 * @brief Create the module and extract all the needed information from the configuration file.
 * @param[in]  xmlconfigFile   path to the file containing the XML description of the TRDP packets.
 * @return TRDP_PARSEBODY_OK when no errors occured
 */
TRDP_RET_t trdp_parsebody_init(const char ** xmlconfigFile);


/** @fn void trdp_parsebody_clean(void)
 * @brief Clean used memory
 *
 * Release all the allocated memory, needed to store the given information.
 * @return nothing
 */
void trdp_parsebody_clean(void);

/** @fn int trdp_parsebody_isinited( void )
 * Show the status, if the library is ready to use.
 * @return > 0 if the library is initialized, 0 if uninitialized
 */
int trdp_parsebody_isinited( void );

/** @fn struct Dataset* trdp_parsebody_lookup(guint32 comId)
 * Looks up the dataset for a given ComId.
 * @param[in] comId    to search for.
 * @return NULL, when nothing was found.
 */
struct Dataset* trdp_parsebody_lookup(guint32 comId);

/** @fn struct Dataset* trdp_parsebody_search(guint32 datasetId)
 * Uses the second hashmap to find the struct Dataset for a given datasetid
 * @param[in]   datasetId       the dataset we are searching for
 * @return NULL, when nothing was found.
 */
struct Dataset* trdp_parsebody_search(guint32 datasetId);

#endif
