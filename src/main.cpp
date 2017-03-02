//#include "fs/romfs/fileSystemHeader.hpp"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include <boost/sml.hpp>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
// #include "stm32f4xx_rcc.h"
#include "kernel.hpp"
#include "logger.hpp"
// #include "usart.hpp"
#include "bootloader.hpp"
#include "types.h"
#include "utils.hpp"
// //#include <stdio.h>
// //#include "usart.hpp"
// #include "kernel.hpp"
// #include "logger.hpp"
// #include "usart.hpp"
// #include <cstdio>
// #include <cstdlib>
#include "usart.hpp"


void initializeBoardLeds()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}


// namespace sml = boost::sml;

// struct release
// {
// };
// struct ack
// {
// };
// struct fin
// {
// };
// struct timeout
// {
// };

// const auto is_ack_valid = [](const ack&) { return true; };
// const auto is_fin_valid = [](const fin&) { return true; };

// const auto send_fin = [] {};
// const auto send_ack = [] {};

// class established;
// class fin_wait_1;
// class fin_wait_2;
// class timed_wait;

// struct hello_world
// {
//     auto operator()() const
//     {
//         using namespace sml;
//         return make_transition_table(
//             *state<established> + event<release> / send_fin = state<fin_wait_1>,
//             state<fin_wait_1> + event<ack>[is_ack_valid] = state<fin_wait_2>,
//             state<fin_wait_2> + event<fin>[is_fin_valid] / send_ack = state<timed_wait>,
//             state<timed_wait> + event<timeout> / send_ack = X);
//     }
// };

int main(void)
{
    SystemInit();
    //hw::USART<hw::USARTS::USART2_PP1>::getUsart();
    hw::USART<hw::USARTS::USART1_PP1>::getUsart();
    //u1.init();

    Logger logger("boot\0");
    initializeBoardLeds();
    GPIO_SetBits(GPIOD, GPIO_Pin_14);


    hardwareInitialize();

    BootLoader bl(logger);
    //logger << Level::INFO << "Bootloader started\r";

    //logger << Level::INFO << "allocated on: " << (int)test << "\n";

    /*if (bl.specialMode())
    {
        logger << Level::INFO << "Boot in special mode\n";
        bl.bootSpecialMode();
    }
    else
    {
        logger << Level::INFO << "Boot FW\n";
        bl.bootFW();
    }*/

    // sml::sm<hello_world> sm;

    // sm.process_event(release{});

    // sm.process_event(ack{});

    // sm.process_event(fin{});

    // sm.process_event(timeout{});


    //  while (1)
    //    {
    //    }
}


void assert_failed(u8* file, u32 line)
{
    write(0, file, strlen((char*)file));
    write(0, ":", 1);
    char buf[10];
    utils::itoa(line, buf, 10);
    write(0, buf, strlen(buf));
    write(0, " assertion failed!", 18);
    while (true)
    {
    }
}
