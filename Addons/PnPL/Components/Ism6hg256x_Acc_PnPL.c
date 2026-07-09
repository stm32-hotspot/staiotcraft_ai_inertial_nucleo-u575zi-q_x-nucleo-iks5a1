/**
  ******************************************************************************
  * @file    Ism6hg256x_Acc_PnPL.c
  * @author  SRA
  * @brief   Ism6hg256x_Acc PnPL Component Manager
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *
  ******************************************************************************
  */

/**
  ******************************************************************************
  * This file has been auto generated from the following DTDL Component:
  * dtmi:appconfig:nucleo_u575zi_q:STAIOTCRAFT_AI_Inertial:sensors:ism6hg256x_acc;1
  *
  * Created by: DTDL2PnPL_cGen version 3.1.0-alpha.2
  *
  * WARNING! All changes made to this file will be lost if this is regenerated
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "App_model.h"
#include "IPnPLComponent.h"
#include "IPnPLComponent_vtbl.h"
#include "PnPLCompManager.h"

#include "Ism6hg256x_Acc_PnPL.h"

static const IPnPLComponent_vtbl sIsm6hg256x_Acc_PnPL_CompIF_vtbl =
{
  Ism6hg256x_Acc_PnPL_vtblGetKey,
  Ism6hg256x_Acc_PnPL_vtblGetNCommands,
  Ism6hg256x_Acc_PnPL_vtblGetCommandKey,
  Ism6hg256x_Acc_PnPL_vtblGetStatus,
  Ism6hg256x_Acc_PnPL_vtblSetProperty,
  Ism6hg256x_Acc_PnPL_vtblExecuteFunction
};

/**
  *  Ism6hg256x_Acc_PnPL internal structure.
  */
struct _Ism6hg256x_Acc_PnPL
{
  /* Implements the IPnPLComponent interface. */
  IPnPLComponent_t component_if;
};

/* Objects instance ----------------------------------------------------------*/
static Ism6hg256x_Acc_PnPL sIsm6hg256x_Acc_PnPL;

/* Public API definition -----------------------------------------------------*/
IPnPLComponent_t *Ism6hg256x_Acc_PnPLAlloc()
{
  IPnPLComponent_t *pxObj = (IPnPLComponent_t *) &sIsm6hg256x_Acc_PnPL;
  if (pxObj != NULL)
  {
    pxObj->vptr = &sIsm6hg256x_Acc_PnPL_CompIF_vtbl;
  }
  return pxObj;
}

uint8_t Ism6hg256x_Acc_PnPLInit(IPnPLComponent_t *_this)
{
  IPnPLComponent_t *component_if = _this;
  PnPLAddComponent(component_if);
  ism6hg256x_acc_comp_init();
  return PNPL_NO_ERROR_CODE;
}


/* IPnPLComponent virtual functions definition -------------------------------*/
char *Ism6hg256x_Acc_PnPL_vtblGetKey(IPnPLComponent_t *_this)
{
  return ism6hg256x_acc_get_key();
}

uint8_t Ism6hg256x_Acc_PnPL_vtblGetNCommands(IPnPLComponent_t *_this)
{
  return 0;
}

char *Ism6hg256x_Acc_PnPL_vtblGetCommandKey(IPnPLComponent_t *_this, uint8_t id)
{
  return "";
}

uint8_t Ism6hg256x_Acc_PnPL_vtblGetStatus(IPnPLComponent_t *_this, char **serializedJSON, uint32_t *size,
                                          uint8_t pretty)
{
  JSON_Value *tempJSON;
  JSON_Object *JSON_Status;

  tempJSON = json_value_init_object();
  JSON_Status = json_value_get_object(tempJSON);

  pnpl_ism6hg256x_acc_odr_t temp_odr_e = (pnpl_ism6hg256x_acc_odr_t)0;
  ism6hg256x_acc_get_odr(&temp_odr_e);
  json_object_dotset_number(JSON_Status, "ism6hg256x_acc.odr", temp_odr_e);
  pnpl_ism6hg256x_acc_fs_t temp_fs_e = (pnpl_ism6hg256x_acc_fs_t)0;
  ism6hg256x_acc_get_fs(&temp_fs_e);
  json_object_dotset_number(JSON_Status, "ism6hg256x_acc.fs", temp_fs_e);
  /* Next fields are not in DTDL model but added looking @ the component schema
  field (this is :sensors). ONLY for Sensors, Algorithms and Actuators*/
  json_object_dotset_number(JSON_Status, "ism6hg256x_acc.c_type", COMP_TYPE_SENSOR);
  int8_t temp_int8 = 0;
  ism6hg256x_acc_get_stream_id(&temp_int8);
  json_object_dotset_number(JSON_Status, "ism6hg256x_acc.stream_id", temp_int8);
  ism6hg256x_acc_get_ep_id(&temp_int8);
  json_object_dotset_number(JSON_Status, "ism6hg256x_acc.ep_id", temp_int8);

  if (pretty == 1)
  {
    *serializedJSON = json_serialize_to_string_pretty(tempJSON);
    *size = json_serialization_size_pretty(tempJSON);
  }
  else
  {
    *serializedJSON = json_serialize_to_string(tempJSON);
    *size = json_serialization_size(tempJSON);
  }

  /* No need to free temp_j as it is part of tempJSON */
  json_value_free(tempJSON);

  return PNPL_NO_ERROR_CODE;
}

uint8_t Ism6hg256x_Acc_PnPL_vtblSetProperty(IPnPLComponent_t *_this, char *serializedJSON)
{
  return PNPL_NO_ERROR_CODE;
}


uint8_t Ism6hg256x_Acc_PnPL_vtblExecuteFunction(IPnPLComponent_t *_this, char *serializedJSON)
{
  return PNPL_NO_COMMANDS_ERROR_CODE;
}

