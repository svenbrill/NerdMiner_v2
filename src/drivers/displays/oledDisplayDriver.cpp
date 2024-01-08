#include <heltec.h>
#include "displayDriver.h"
#include "monitor.h"
#include "version.h"

#ifdef OLED_DISPLAY

#define WIDTH 128
#define HEIGHT 64

SSD1306Wire *display;

void oledDisplay_Init(void)
{
  display = new SSD1306Wire(0x3c, SDA_OLED, SCL_OLED, RST_OLED, GEOMETRY_128_64);
  display->init();
  display->setColor(WHITE);
  display->clear();
}

void oledDisplay_AlternateScreenState(void)
{
  Serial.println("Switching display state");
}

void oledDisplay_AlternateRotation(void)
{
}

void oledDisplay_CustomScreen(unsigned long mElapsed)
{
  mining_data data = getMiningData(mElapsed);

  Serial.printf(">>> Completed %s share(s), %s Khashes, avg. hashrate %s KH/s\n",
                data.completedShares.c_str(), data.totalKHashes.c_str(), data.currentHashRate.c_str());

  display->clear();

  // Current hashrate
  display->setFont(ArialMT_Plain_24);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(display->getWidth() / 2, 4, (String)data.currentHashRate.c_str() + " KH/s");

  // Valid Blocks
  display->setFont(ArialMT_Plain_16);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(display->getWidth() / 2, 32, "Valid Blocks: " + (String)data.valids.c_str());

  // Temprature
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 52, "Temp: " + (String)data.temp.c_str() + "°C");

  // Mining time
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(display->width(), 52, "d" + (String)data.timeMining.c_str());

  display->display();
}

void oledDisplay_MinerScreen(unsigned long mElapsed)
{
  mining_data data = getMiningData(mElapsed);

  Serial.printf(">>> Completed %s share(s), %s Khashes, avg. hashrate %s KH/s\n",
                data.completedShares.c_str(), data.totalKHashes.c_str(), data.currentHashRate.c_str());

  display->clear();

  // Current hashrate
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 0, (String)data.currentHashRate.c_str() + " KH/s");

  // Current time
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString((display->getWidth() / 5) * 3, 0, data.currentTime.c_str());

  // Print Temp
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(display->getWidth(), 0, (String)data.temp.c_str() + "°C");

  // Total hashes
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 10, "Total Million Hashes:");
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(display->getWidth(), 10, data.totalMHashes.c_str());

  // Valid Blocks
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 20, "Valid Blocks:");
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(display->getWidth(), 20, data.valids.c_str());

  // Block templates
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 30, "Block Templates:");
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(display->getWidth(), 30, data.templates.c_str());

  // Best diff
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 40, "Best Difficulty:");
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(display->getWidth(), 40, data.bestDiff.c_str());

  // Mining time
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 50, "Mining Time:");
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(display->getWidth(), 50, "d" + (String)data.timeMining.c_str());

  display->display();
}

void oledDisplay_ClockScreen(unsigned long mElapsed)
{
  clock_data data = getClockData(mElapsed);

  Serial.printf(">>> Completed %s share(s), %s Khashes, avg. hashrate %s KH/s\n",
                data.completedShares.c_str(), data.totalKHashes.c_str(), data.currentHashRate.c_str());

  display->clear();

  // Print Hour
  display->setFont(ArialMT_Plain_16);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(display->getWidth() / 2, 0, data.currentTime.c_str());

  // Hashrate
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 20, "Hashrate:");
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(display->width(), 20, (String)data.currentHashRate.c_str() + " KH/s");

  // Print BTC Price
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 30, "BTC Price:");
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(display->width(), 30, data.btcPrice.c_str());

  // Print BlockHeight
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 40, "Current Block:");
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(display->getWidth(), 40, data.blockHeight.c_str());

  // 32Bit shares
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 50, "32-Bit Shares:");
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(display->getWidth(), 50, data.completedShares.c_str());

  display->display();
}

void oledDisplay_GlobalHashScreen(unsigned long mElapsed)
{
  coin_data data = getCoinData(mElapsed);

  Serial.printf(">>> Completed %s share(s), %s Khashes, avg. hashrate %s KH/s\n",
                data.completedShares.c_str(), data.totalKHashes.c_str(), data.currentHashRate.c_str());

  display->clear();

  // Hashrate
  display->setFont(ArialMT_Plain_16);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(display->width() / 2, 0, (String)data.currentHashRate.c_str() + " KH/s");

  // Print BTC Price
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 20, "Bitcoin Price:");
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(display->width(), 20, data.btcPrice.c_str());

  // Print Global Hashrate
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 30, "Global Hashrate:");
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(display->width(), 30, (String)data.globalHashRate.c_str() + "EH/s");

  // Print BlockHeight
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 40, "Current Block:");
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(display->width(), 40, data.blockHeight.c_str());

  // Print Remaining BLocks
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(0, 50, "Remaining Blocks:");
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(display->width(), 50, data.remainingBlocks.c_str());

  display->display();
}

void oledDisplay_LoadingScreen(void)
{
  display->clear();

  display->setFont(ArialMT_Plain_16);
  display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display->drawString(display->getWidth() / 2, (display->getHeight() / 2) - 10, "NerdMinerV2");
  display->drawString(display->getWidth() / 2, (display->getHeight() / 2) + 10, CURRENT_VERSION);

  display->display();
}

void oledDisplay_SetupScreen(void)
{
  display->clear();

  display->setFont(ArialMT_Plain_16);
  display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display->drawString(display->getWidth() / 2, (display->getHeight() / 2), "Setup...");

  display->display();
}

void oledDisplay_AnimateCurrentScreen(unsigned long frame)
{
}

void oledDisplay_DoLedStuff(unsigned long frame)
{
}

CyclicScreenFunction oledDisplayCyclicScreens[] = {oledDisplay_CustomScreen, oledDisplay_MinerScreen, oledDisplay_ClockScreen, oledDisplay_GlobalHashScreen};

DisplayDriver oledDisplayDriver = {
    oledDisplay_Init,
    oledDisplay_AlternateScreenState,
    oledDisplay_AlternateRotation,
    oledDisplay_LoadingScreen,
    oledDisplay_SetupScreen,
    oledDisplayCyclicScreens,
    oledDisplay_AnimateCurrentScreen,
    oledDisplay_DoLedStuff,
    SCREENS_ARRAY_SIZE(oledDisplayCyclicScreens),
    0,
    WIDTH,
    HEIGHT};
#endif
