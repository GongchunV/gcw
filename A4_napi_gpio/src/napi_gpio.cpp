#include <stdio.h>      //c基本头文件
//#include <stdlib.h>    //goto函数
#include <stdint.h>    //uint8_t
#include <unistd.h>     //sleep


#include "hdf_log.h"    //路径：    "//drivers/hdf_core/interfaces/inner_api/utils",
#include "gpio_if.h"    //路径：    "//drivers/hdf_core/framework/include/platform",

#include "napi/native_api.h"


void gpio_init(){
    printf("gpio_test begin\r\n");
    printf("---------------------------\n");
    int32_t ret;  //32位返回值
    uint16_t pin=114;   //pin value 114
    ret= GpioSetDir(pin,GPIO_DIR_OUT);
    if(ret==0){
        printf("gpiosetdir successfully!");
        HDF_LOGI("HDF_LOGI:gpiosetdir successfully!");
    }
    else{
        printf("gpiosetdir failed!");
        HDF_LOGE("HDF_LOGE:gpiosetdir failed!");
    }
    
    printf("---------------------------\n");
    return 0;
}

static napi_value Add(napi_env env, napi_callback_info info)
{
    size_t requireArgc = 2;
    size_t argc = 2;
    napi_value args[2] = {nullptr};

    napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);

    napi_valuetype valuetype0;
    napi_typeof(env, args[0], &valuetype0);

    napi_valuetype valuetype1;
    napi_typeof(env, args[1], &valuetype1);

    double value0;
    napi_get_value_double(env, args[0], &value0);

    double value1;
    napi_get_value_double(env, args[1], &value1);

    if(value0==0){
        ret=GpioWrite(pin,1);
        if(ret==-1){
            printf("write failed,led on failed");
        }
    }
    if(value1==0){
        ret=GpioWrite(pin,1);
        if(ret==-1){
            printf("write failed,led off failed");
        }
    }

    napi_value sum;
    napi_create_double(env, value0 + value1, &sum);

    return sum;

}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "add", nullptr, Add, nullptr, nullptr, nullptr, napi_default, nullptr }
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "gpio_hdf",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterNAPI_firstModule(void)
{
    napi_module_register(&demoModule);
}




