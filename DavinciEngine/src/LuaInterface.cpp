/*
** Lua binding: LuaInterface
** Generated automatically by tolua++-1.0.93-lua53 on Tue Jul 18 06:14:07 2023.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_LuaInterface_open (lua_State* tolua_S);

#include "DavinciEngine.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"DavinciEngine::Davinci");
}

/* method: Engine_GetInstance of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_Engine_GetInstance00
static int tolua_LuaInterface_DavinciEngine_Davinci_Engine_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DavinciEngine::Davinci* tolua_ret = (DavinciEngine::Davinci*)  DavinciEngine::Davinci::Engine_GetInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DavinciEngine::Davinci");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Engine_GetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Engine_Destroy of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_Engine_Destroy00
static int tolua_LuaInterface_DavinciEngine_Davinci_Engine_Destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Engine_Destroy'", NULL);
#endif
  {
   self->Engine_Destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Engine_Destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Engine_Init of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_Engine_Init00
static int tolua_LuaInterface_DavinciEngine_Davinci_Engine_Init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Engine_Init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Engine_Init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Engine_Init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Engine_Update of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_Engine_Update00
static int tolua_LuaInterface_DavinciEngine_Davinci_Engine_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Engine_Update'", NULL);
#endif
  {
   self->Engine_Update();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Engine_Update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TimerStart of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_TimerStart00
static int tolua_LuaInterface_DavinciEngine_Davinci_TimerStart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TimerStart'", NULL);
#endif
  {
   self->TimerStart();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TimerStart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TimerPause of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_TimerPause00
static int tolua_LuaInterface_DavinciEngine_Davinci_TimerPause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TimerPause'", NULL);
#endif
  {
   self->TimerPause();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TimerPause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TimerGetTicks of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_TimerGetTicks00
static int tolua_LuaInterface_DavinciEngine_Davinci_TimerGetTicks00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TimerGetTicks'", NULL);
#endif
  {
   float tolua_ret = (float)  self->TimerGetTicks();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TimerGetTicks'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGameMode of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_GetGameMode00
static int tolua_LuaInterface_DavinciEngine_Davinci_GetGameMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGameMode'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetGameMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGameMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetGameMode of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_SetGameMode00
static int tolua_LuaInterface_DavinciEngine_Davinci_SetGameMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
  int mode = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetGameMode'", NULL);
#endif
  {
   self->SetGameMode(mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetGameMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RunScript of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_RunScript00
static int tolua_LuaInterface_DavinciEngine_Davinci_RunScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
  const char* scriptFile = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RunScript'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->RunScript(scriptFile);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RunScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetResolution of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_SetResolution00
static int tolua_LuaInterface_DavinciEngine_Davinci_SetResolution00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
  int windowWidth = ((int)  tolua_tonumber(tolua_S,2,0));
  int windowHeight = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetResolution'", NULL);
#endif
  {
   self->SetResolution(windowWidth,windowHeight);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetResolution'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFullscreen of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_SetFullscreen00
static int tolua_LuaInterface_DavinciEngine_Davinci_SetFullscreen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
  bool fullscreen = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFullscreen'", NULL);
#endif
  {
   self->SetFullscreen(fullscreen);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFullscreen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsFullscreen of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_IsFullscreen00
static int tolua_LuaInterface_DavinciEngine_Davinci_IsFullscreen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsFullscreen'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsFullscreen();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsFullscreen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWindowWidth of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_GetWindowWidth00
static int tolua_LuaInterface_DavinciEngine_Davinci_GetWindowWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWindowWidth'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetWindowWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWindowWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWindowHeight of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_GetWindowHeight00
static int tolua_LuaInterface_DavinciEngine_Davinci_GetWindowHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWindowHeight'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetWindowHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWindowHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Engine_Log of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_Engine_Log00
static int tolua_LuaInterface_DavinciEngine_Davinci_Engine_Log00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
  const char* message = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Engine_Log'", NULL);
#endif
  {
   self->Engine_Log(message);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Engine_Log'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Engine_Error of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_Engine_Error00
static int tolua_LuaInterface_DavinciEngine_Davinci_Engine_Error00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
  const char* error = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Engine_Error'", NULL);
#endif
  {
   self->Engine_Error(error);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Engine_Error'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearScene of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_ClearScene00
static int tolua_LuaInterface_DavinciEngine_Davinci_ClearScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearScene'", NULL);
#endif
  {
   self->ClearScene();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadActor of class  DavinciEngine::Davinci */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_DavinciEngine_Davinci_LoadActor00
static int tolua_LuaInterface_DavinciEngine_Davinci_LoadActor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DavinciEngine::Davinci",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DavinciEngine::Davinci* self = (DavinciEngine::Davinci*)  tolua_tousertype(tolua_S,1,0);
  const char* type = ((const char*)  tolua_tostring(tolua_S,2,0));
  float xPos = ((float)  tolua_tonumber(tolua_S,3,0));
  float yPos = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadActor'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->LoadActor(type,xPos,yPos);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadActor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_LuaInterface_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"DavinciEngine",0);
  tolua_beginmodule(tolua_S,"DavinciEngine");
   tolua_cclass(tolua_S,"Davinci","DavinciEngine::Davinci","",NULL);
   tolua_beginmodule(tolua_S,"Davinci");
    tolua_function(tolua_S,"Engine_GetInstance",tolua_LuaInterface_DavinciEngine_Davinci_Engine_GetInstance00);
    tolua_function(tolua_S,"Engine_Destroy",tolua_LuaInterface_DavinciEngine_Davinci_Engine_Destroy00);
    tolua_function(tolua_S,"Engine_Init",tolua_LuaInterface_DavinciEngine_Davinci_Engine_Init00);
    tolua_function(tolua_S,"Engine_Update",tolua_LuaInterface_DavinciEngine_Davinci_Engine_Update00);
    tolua_function(tolua_S,"TimerStart",tolua_LuaInterface_DavinciEngine_Davinci_TimerStart00);
    tolua_function(tolua_S,"TimerPause",tolua_LuaInterface_DavinciEngine_Davinci_TimerPause00);
    tolua_function(tolua_S,"TimerGetTicks",tolua_LuaInterface_DavinciEngine_Davinci_TimerGetTicks00);
    tolua_function(tolua_S,"GetGameMode",tolua_LuaInterface_DavinciEngine_Davinci_GetGameMode00);
    tolua_function(tolua_S,"SetGameMode",tolua_LuaInterface_DavinciEngine_Davinci_SetGameMode00);
    tolua_function(tolua_S,"RunScript",tolua_LuaInterface_DavinciEngine_Davinci_RunScript00);
    tolua_function(tolua_S,"SetResolution",tolua_LuaInterface_DavinciEngine_Davinci_SetResolution00);
    tolua_function(tolua_S,"SetFullscreen",tolua_LuaInterface_DavinciEngine_Davinci_SetFullscreen00);
    tolua_function(tolua_S,"IsFullscreen",tolua_LuaInterface_DavinciEngine_Davinci_IsFullscreen00);
    tolua_function(tolua_S,"GetWindowWidth",tolua_LuaInterface_DavinciEngine_Davinci_GetWindowWidth00);
    tolua_function(tolua_S,"GetWindowHeight",tolua_LuaInterface_DavinciEngine_Davinci_GetWindowHeight00);
    tolua_function(tolua_S,"Engine_Log",tolua_LuaInterface_DavinciEngine_Davinci_Engine_Log00);
    tolua_function(tolua_S,"Engine_Error",tolua_LuaInterface_DavinciEngine_Davinci_Engine_Error00);
    tolua_function(tolua_S,"ClearScene",tolua_LuaInterface_DavinciEngine_Davinci_ClearScene00);
    tolua_function(tolua_S,"LoadActor",tolua_LuaInterface_DavinciEngine_Davinci_LoadActor00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_LuaInterface (lua_State* tolua_S) {
 return tolua_LuaInterface_open(tolua_S);
};
#endif

