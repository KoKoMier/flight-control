#include <iostream>
#include "src/SPI/LinuxSPI.hpp"
#include <chrono>
#include <unistd.h>
#include <iomanip>
#include <cmath>
#include "src/PAC9685/pac.hpp"
#include "src/UART/CRSFProtocol.hpp"
#include "src/UART/CRSFUartRC.hpp"
#include <sys/time.h>
#include <thread>
#include "src/UART/uart.hpp"
#include <string>
#include <mutex>
#include "src/MPU6500/MPU6500.hpp"
#include "src/CONTROL/control.hpp"

float pid_p_gain_roll = 0;
float pid_i_gain_roll = 0;
float pid_d_gain_roll = 0;

float pid_p_gain_pitch = 0;
float pid_i_gain_pitch = 0;
float pid_d_gain_pitch = 0;

int signalIn = 0;
int TimestartUpLoad = 0;

float pid_roll_error = 0;
float gyro_roll_input = 0;
float pid_roll_setpoint = 0;
float pid_i_sum_roll = 0;
float pid_output_roll = 0;
float pid_last_d_err = 0;

int pwmValue[4] = {1800, 1800, 1800, 1800};

int pin1 = 13;
int pin2 = 15;
int pin3 = 14;
int pin4 = 12;
int Servos1 = 0;
int Servos2 = 1;
int Servos3 = 2;

CONTROL control;
CRSF test;

void dataParese(std::string data, std::string *databuff, const char splti, int MaxSize)
{
    std::istringstream f(data);
    std::string s;
    int count = 0;
    while (getline(f, s, splti))
    {
        if (count > MaxSize)
            break;
        databuff[count] = s;
        count++;
    }
}

float limitValue(float value)
{
    if (value > 2000)
    {
        return 2000;
    }
    else
    {
        return value;
    }
}

int GetTimestamp()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * (uint64_t)1000000 + tv.tv_usec));
}

int main(int argc, char *argv[])
{
    int argvs;

    TimestartUpLoad = GetTimestamp();

    while ((argvs = getopt(argc, argv, "s::g::r::c::f::R")) != -1)
    {
        switch (argvs)
        {

        case 's':
        {
            SensorsAcorrect();

            while (true)
            {
                int microstart = GetTimestamp();
                // control.control();
                SensorsParse();
                //
                // std::cout << "---------------------------"
                //          << "\r\n";
                // std::cout << "mpu_6500_GX:" << std::fixed << std::setprecision(5) << mpu_6500_GX << "\r\n";
                // std::cout << "mpu_6500_GY:" << std::fixed << std::setprecision(5) << mpu_6500_GY << "\r\n";
                // std::cout << "mpu_6500_GZ:" << std::fixed << std::setprecision(5) << mpu_6500_GZ << "\r\n";
                // std::cout << "---------------------------"
                //         << "\r\n";
                // std::cout << "Angle_Pitch_Out:" << std::fixed << std::setprecision(1) << Angle_Pitch_Out << "\r\n";
                // std::cout << "Angle_Roll_Out:" << std::fixed << std::setprecision(1) << Angle_Roll_Out << "\r\n";
                // std::cout << "Tmp_AY:" << std::fixed << std::setprecision(2) << mpu_6500_AY
                //         << "\r\n";
                // std::cout << "---------------------------"
                //          << "\r\n";
                int microend = GetTimestamp();
                if (microend - microstart < 4000)
                {
                    usleep(4000 - (microend - microstart)); // 250Hz
                }
            }
        }
        break;

        case 'f':
        {
            while (true)
            {
                FILE *file = fopen("./data/example.txt", "w");
                if (file == NULL)
                {
                    printf("无法打开文件\n");
                    return 1;
                }

                for (int i = 1; i <= 6; i++)
                {
                    int sp;
                    switch (i)
                    {
                    case 1:
                    {
                        std::cout << "请将无人机放平"
                                  << "\r\n";
                        std::cin >> sp;
                        SensorsAcorrect();
                        std::cout << "_mpu_6500_AZ_Cali:" << _mpu_6500_AZ_Cali << "\r\n";
                        fprintf(file, "Orthogonal data:%f\n", _mpu_6500_AZ_Cali);
                    }
                    break;
                    case 2:
                    {
                        std::cout << "请将无人机倒放"
                                  << "\r\n";
                        std::cin >> sp;
                        SensorsAcorrect();
                        std::cout << "_mpu_6500_AZ_Cali:" << _mpu_6500_AZ_Cali << "\r\n";
                        fprintf(file, "Inverted data:%f\n", _mpu_6500_AZ_Cali);
                    }
                    break;
                    case 3:
                    {
                        std::cout << "请将无人机左侧放"
                                  << "\r\n";
                        std::cin >> sp;
                        SensorsAcorrect();
                        std::cout << "_mpu_6500_AX_Cali:" << _mpu_6500_AX_Cali << "\r\n";
                        fprintf(file, "Left data:%f\n", _mpu_6500_AX_Cali);
                    }
                    break;
                    case 4:
                    {
                        std::cout << "请将无人机右侧放"
                                  << "\r\n";
                        std::cin >> sp;
                        SensorsAcorrect();
                        std::cout << "_mpu_6500_AX_Cali:" << _mpu_6500_AX_Cali << "\r\n";
                        fprintf(file, "Right data:%f\n", _mpu_6500_AX_Cali);
                    }
                    break;
                    case 5:
                    {
                        std::cout << "请将无人机前侧放"
                                  << "\r\n";
                        std::cin >> sp;
                        SensorsAcorrect();
                        std::cout << "_mpu_6500_AX_Cali:" << _mpu_6500_AY_Cali << "\r\n";
                        fprintf(file, "Front data:%f\n", _mpu_6500_AY_Cali);
                    }
                    break;
                    case 6:
                    {
                        std::cout << "请将无人机后侧放"
                                  << "\r\n";
                        std::cin >> sp;
                        SensorsAcorrect();
                        std::cout << "_mpu_6500_AX_Cali:" << _mpu_6500_AY_Cali << "\r\n";
                        fprintf(file, "Back  data:%f\n", _mpu_6500_AY_Cali);
                    }
                    break;
                    }
                }
                std::cout << "初始化完毕"
                          << "\r\n";
                fclose(file);

                return 0;
            }
        }
        break;

        case 'g':
        {
            int fd = pca9685Setup("/dev/i2c-7", 0x70, 400);
            while (true)
            {
                int sp;
                std::cin >> sp;
                pca9685PWMWrite(fd, 16, 0, sp);
                std::cout << sp << std::endl;
            }

            // int fd = open("/dev/ttyS1", O_RDWR | O_NOCTTY);
            // char buff[8];

            // set_serial(fd, 115200, 8, 'N', 1);
            // while (true)
            // {
            //     read(fd, buff, 8);

            //     usleep(20000);
            //     std::cout << "distance: " << buff << "\r\n";
            // }
        }
        break;

        case 'R':
        {
            long int time;
            long int timee;
            CRSF test;
            int channelData[50];

            while (true)
            {
                time = GetTimestamp() - TimestartUpLoad;
                //
                int retValue = test.CRSFRead(channelData);
                if (retValue > 0)
                {

                    std::cout << test.rcToUs(channelData[0]) << "\r\n";
                    std::cout << test.rcToUs(channelData[1]) << "\r\n";
                    std::cout << test.rcToUs(channelData[2]) << "\r\n";
                    std::cout << test.rcToUs(channelData[3]) << "\r\n";
                    std::cout << test.rcToUs(channelData[4]) << "\r\n";
                    std::cout << test.rcToUs(channelData[5]) << "\r\n";
                    std::cout << test.rcToUs(channelData[6]) << "\r\n";
                    std::cout << test.rcToUs(channelData[7]) << "\r\n";
                }
                else
                {
                    std::cout << "error frame recived"
                              << "\n";
                }
                //
                timee = GetTimestamp() - TimestartUpLoad;
                std::cout << "ret: " << retValue
                          << " last frame time : " << timee - time << " "
                          << "\n"
                          << std::endl;
            }
        }
        break;

        case 'c':
        {
            SensorsAcorrect();

            int channelData[50];

            int fd = pca9685Setup("/dev/i2c-7", 0x70, 400);
            char input = ' ';

            int fd1 = open("/dev/ttyS1", O_RDWR | O_NOCTTY);
            char buff[8] = {0};
            set_serial(fd1, 115200, 8, 'N', 1);

            struct termios old_tio, new_tio;
            tcgetattr(STDIN_FILENO, &old_tio);
            new_tio = old_tio;
            new_tio.c_lflag &= (~ICANON & ~ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

            std::thread inputThread([&fd]
                                    {
                while (true){
                    int microstart = GetTimestamp();
                    control.control();
                    
                    // pca9685PWMWriteS(fd, pin1, limitValue(pwmValue[0]));
                    // pca9685PWMWriteS(fd, pin2, limitValue(pwmValue[1]));
                    // pca9685PWMWriteS(fd, pin3, limitValue(pwmValue[2]));
                    // pca9685PWMWriteS(fd, pin4, limitValue(pwmValue[3]));

                    std::cout << "pwmValue = " << pwmValue[0] << "\r\n";
                    std::cout << "pwmValue = " << pwmValue[1] << "\r\n";
                    std::cout << "pwmValue = " << pwmValue[2] << "\r\n";
                    std::cout << "pwmValue = " << pwmValue[3] << "\r\n";
                    int microend = GetTimestamp();
                    if(microend - microstart < 5000)
                    {
                        usleep(5000 - (microend - microstart)); // 200Hz
                    }
                // std::cout << "time = " << microend - microstart << "\r\n";
                } });

            std::thread inputThread1([&channelData]
                                     {
                while (true){
                    int microstart = GetTimestamp();
                    int retValue = test.CRSFRead(channelData);
                    if (retValue > 0)
                    {
                        crsf.original_throttle = test.rcToUs(channelData[1]) - 1117;
                        crsf.original_yaw = test.rcToUs(channelData[0]);
                        crsf.original_pitch = test.rcToUs(channelData[2]) - 1628;
                        crsf.original_roll = test.rcToUs(channelData[3]);
                        crsf.original_key1 = test.rcToUs(channelData[6]);
                        crsf.original_key2 = test.rcToUs(channelData[4]);
                        crsf.original_key3 = test.rcToUs(channelData[5]);
                        crsf.original_key4 = test.rcToUs(channelData[7]);

                        // std::cout << "1" << test.rcToUs(channelData[0]) << "\r\n"; // yaw 1093-2012
                        // std::cout << "2" << test.rcToUs(channelData[1]) << "\r\n"; // up 1117-2012
                        // std::cout << "3" << test.rcToUs(channelData[2]) << "\r\n"; // pitch 1117-2012
                        // std::cout << "4" << test.rcToUs(channelData[3]) << "\r\n"; // roll 989-1462
                        // std::cout << "5" << test.rcToUs(channelData[4]) << "\r\n"; // key[1] 1000 2000
                        // std::cout << "6" << test.rcToUs(channelData[5]) << "\r\n"; // key2[0] 1000 1503 2000
                        // std::cout << "7" << test.rcToUs(channelData[6]) << "\r\n"; // key[0] 1000 2000
                        // std::cout << "8" << test.rcToUs(channelData[7]) << "\r\n"; // key2[1] 1000 1503 2000

                    }
                    else
                    {
                        // std::cout << "error frame recived"
                        //         << "\n";
                    }
                    int microend = GetTimestamp();
                    if(microend - microstart < 5000)
                    {
                        usleep(5000 - (microend - microstart)); // 200Hz
                    }
                //std::cout << "time = " << microend - microstart << "\r\n";
                } });

            while (true)
            {
                int microstart = GetTimestamp();

                SensorsParse();

                // std::cout << "Angle_Pitch:" << std::fixed << std::setprecision(1) << Angle_Pitch_Out << "\r\n";
                // std::cout << "Angle_Roll:" << std::fixed << std::setprecision(1) << Angle_Roll_Out << "\r\n";
                // std::cout << "------------------------------------"
                //           << "\r\n";

                int microend = GetTimestamp();
                if (microend - microstart < 4000)
                {
                    usleep(4000 - (microend - microstart)); // 250Hz
                }
                // std::cout << "time = " << microend - microstart << "\r\n";
            }
            tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
        }
        break;
        }
    }
}