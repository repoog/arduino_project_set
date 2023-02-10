## Arduino项目合集

该项目合集是本人尝试并试验过的Arduino相关的代码合集，历史的诸多项目代码由于意外已丢失，因此将Arduino的项目代码在GitHub中维护（好在代码也不多）。后续会逐渐完善试验中的电路图、设备图或传感器图片，以及传感器相关的介绍。

### 项目说明

* ir_remote_fan

通过红外遥控控制电机风扇速度，通过遥控器的1、2、3键调节风扇转速。

* ir_remote_system

通过红外遥控控制Windows系统，将Arduino UNO的ATmega16u2芯片刷Keyboard固件，实现类似BadUSB效果，并结合红外遥控实现。遥控器1键打开资源浏览器，2键回到桌面，3键打开任务栏固定的第三个应用，CH+键关闭系统。

* auto_drug_feeding

通过DFPlayer mini、MG90和SG90舵机构建的旋臂装置，通过该装置可以播放喂药时候的提醒声音以及通过旋臂在固定位置倾倒药物或食物，实现粗糙版本的喂药系统。
