[尝试使用napi，在上层调用gpio来实现点灯]  
## 报错合集  
- ninja: error: '../../gcw/A4_napi_gpio/napi_gpio.cpp', needed by 'obj/gcw/A4_napi_gpio/gpio_hdf/napi_gpio.o', missing and no known rule to make it  
- 加了：external_deps = [   "hdf_core:libhdf_platform",  
- 显示：Exception: deps validation part_name: 'A4', target: '//gcw/A4_napi_gpio:gpio_hdf', dep: '//drivers/hdf_core/adapter/uhdfplatform:libhdf_platform' failed!!!  
- 将 deps中的  "//drivers/hdf_core/adapter/uhdf2/platform:libhdf_platform", 删掉  
- Exception: deps validation part_name: 'A4', target: '//gcw/A4_napi_gpio:gpio_hdf', dep: '//foundation/arkui/napi:ace_napi' failed!!!  
- 留着的napi框架又报错，看来依赖模块只能放到扩展依赖上  
- 删掉    deps = [
    "//foundation/arkui/napi:ace_napi",
  ]  
- 在external_deps中增加  
```  
  external_deps = [
    "c_utils:utils",
    "hdf_core:libhdf_utils",
    "hilog:libhilog",
    "napi:ace_napi",
  ]
```  
```  
 "deps": {
    "components": [
        "c_utils",    
        "hdf_core",
         "hilog",
          "napi"
    ],
```  
- 注：在gn中声明具体部件的具体模块，而在bundle中声明部件  
- --
- ../../drivers/hdf_core/framework/include/platform/gpio_if.h:33:10: fatal error: 'osal_irq.h' file not found
- #include "osal_irq.h"           //中断相关接口
#include "osal_time.h"          //时间相关接口  
- --  
```
../../drivers/hdf_core/framework/include/platform/gpio_if.h:33:10: fatal error: 'osal_irq.h' file not found
#include "osal_irq.h"
         ^~~~~~~~~~~~
1 error generated.
```  
-    "//drivers/hdf_core/framework/include/osal",  











## 构建命令行  
* ./compile.sh ./build.py --product-name rk3568 --build-target gcw/A4_napi_gpio:gpio_hdf  
```
./compile_cancel.sh
```
```  
./compile.sh ./build.py --product-name rk3568 --build-target gcw/A4_napi_gpio:gpio_hdf 
```
```
cdddd
```


