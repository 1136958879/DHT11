# DHT11
This repository is DHT11 code!

这个仓库主要是存放DHT11温湿度传感器的驱动代码！代码已经调试可以使用！为了使用者方便使用已经驱动代码进行封装，只需改动DATA管脚即可使用！

使用教程：

Attention：由于该文件使用了正点原子提供的delay函数，记得在DHT11初始化前记得初始化Delay函数！！

1、先初始化DHT11
```
   DHT11_init();
```

2、读取数据，在读取温湿度数据需要先定义一个结构体！

```
  DHT11_Data_TypeDef DHT11_Data;//定义一个结构体
```

```
if(Read_DHT11(&DHT11_Data) == 1)
{
  humi = DHT11_Data.humi_int + DHT11_Data.humi_deci;
  temp = DHT11_Data.temp_int + DHT11_Data.temp_deci;
  printf("\r\n读取DHT11成功！\r\n\r\n湿度为 %d.%d %RH , 温度为 %d.%d℃ \r\n", \
  DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
	}
```

如果觉得有用的话！记得给我一个star哦！非常感谢！
