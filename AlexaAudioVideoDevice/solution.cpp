class Battery
{
  public:
    Battery(bool isCharging) : isCharging{isCharging}, percentage{0.0d}
    {
    }

    virtual void showBatteryPercentage() 
    {
      return percentage;
    }

    void setBatteryPercentage(double percentage)
    {
      if (doesExist)
          std::cout << "Percentage is : " << percentage << "and charging status is : " << isCharging;
      else
      {
        std::cout << "Battery not available. " << "and charging status is : " << isCharging;
      }
    }
  private: 
    bool isCharging;
    double percentage;
};

class Device
{
  private:
    Battery battery;
  public:
    Device(Battery pBattery) : battery{pBattery}
    {
    }


};

class AudioFeature
{
};

class ScreenFeature
{
};


class AudioDevice : public Device, public AudioFeature
{
};

class ScreenDevice : public Decvice, public ScreenFeature
{
};

class AudioScreenDevice : public Device, public AudioFeature, public ScreenFeature
{
};
