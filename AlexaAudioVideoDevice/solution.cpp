#include <iostream>
#include <memory>

class Battery
{
  public:
    Battery() : percentage{0.0}
    {
    }

    double getBatteryPercentage() const
    {
      return percentage;
    }

    void setBatteryPercentage(double percent)
    {
      this->percentage = percent;
    }

  private: 
    double percentage;
};

class Device
{    
  public:

    virtual void showBatteryPercentage() const = 0;   
    virtual void showFeatures() const = 0;

    virtual bool getChargingStatus() const
    {
      return isCharging;
    }

    virtual void setChargingStatus(bool status)
    {
      this->isCharging = status;
    }

  private: 
    bool isCharging;
};

class BasicDevice : public Device
{
  private:
    std::shared_ptr<Battery> battery;

  public:
    BasicDevice() : battery{nullptr}
    {      
    }

    BasicDevice(std::shared_ptr<Battery> pBattery) : battery{pBattery}
    {
    }

    void showFeatures() const override
    {
      std::cout << "Basic features engaged." << "\n";
    }

    void showBatteryPercentage() const override
    {
      if (battery)
        std::cout << "Battery: " << battery->getBatteryPercentage()
                  << "% | Charging: " << (getChargingStatus() ? "Yes" : "No") << "\n";

      else  
        std::cout << "Battery not available. " << " Charging status is : " << getChargingStatus() << "\n";
    }
};

class AudioFeature
{
  // Audio specific interface methods
};

class ScreenFeature
{
  // Screen specific interface methods
};


class AudioDeviceDecorator : public Device, public AudioFeature
{
  public:
    AudioDeviceDecorator(std::shared_ptr<Device> device) : device{device}
    {
    }

    void showBatteryPercentage() const override
    {
      device->showBatteryPercentage();
    }

    void showFeatures() const override
    {
      this->device->showFeatures();
      std::cout << "Audio features engaged." << "\n";
    }

    bool getChargingStatus() const override
    {
      return device->getChargingStatus();
    }

    void setChargingStatus(bool status) override
    {
      device->setChargingStatus(status);
    }

  private:
    std::shared_ptr<Device> device;
};

class ScreenDeviceDecorator : public Device, public ScreenFeature
{
  public:
    ScreenDeviceDecorator(std::shared_ptr<Device> device) : device{device}
    {
    }

    void showBatteryPercentage() const override
    {
      device->showBatteryPercentage();
    }

    void showFeatures() const override
    {
      this->device->showFeatures();      
      std::cout << "Screen features engaged." << "\n";
    }

    bool getChargingStatus() const override
    {
      return device->getChargingStatus();
    }

    void setChargingStatus(bool status) override
    {
      device->setChargingStatus(status);
    }

  private:
    std::shared_ptr<Device> device;
};

class AlexaSystem
{
  private:
    AlexaSystem() = default;
    AlexaSystem(const AlexaSystem&) = delete;
    AlexaSystem& operator=(const AlexaSystem&) = delete;
  public:    

    static AlexaSystem& getInstance()
    {
      static AlexaSystem instance;
      return instance;
    }

    std::shared_ptr<Device> getAudioDevice()
    {    
      auto basicDevice = std::make_shared<BasicDevice>();
      auto audioBasicDevice = std::make_shared<AudioDeviceDecorator>(basicDevice);

      return audioBasicDevice;
    }

    std::shared_ptr<Device> getScreenDevice()
    {
      auto basicDevice = std::make_shared<BasicDevice>();
      auto screenBasicDevice = std::make_shared<ScreenDeviceDecorator>(basicDevice);

      return screenBasicDevice;
    }

    std::shared_ptr<Device> getAudioScreenDevice()
    {
      auto basicDevice = std::make_shared<BasicDevice>();
      auto audioBasicDevice = std::make_shared<AudioDeviceDecorator>(basicDevice);
      auto screenAudioBasicDevice = std::make_shared<ScreenDeviceDecorator>(audioBasicDevice);

      return screenAudioBasicDevice;
    }
};

int main()
{
  AlexaSystem &instance = AlexaSystem::getInstance();  
  std::cout << "\nAudio device : \n";
  instance.getAudioDevice()->showFeatures();
  std::cout << "\nScreen device : \n";
  instance.getScreenDevice()->showFeatures();
  std::cout << "\nAudio Screen device : \n";
  instance.getAudioScreenDevice()->showFeatures();
  return 0;
}