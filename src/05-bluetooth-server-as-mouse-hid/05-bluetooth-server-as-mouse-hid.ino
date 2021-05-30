#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <BLEHIDDevice.h>

BLEHIDDevice* hid = NULL;
BLEServer *pServer = NULL;
BLEAdvertising *pAdvertising = NULL;

bool deviceConnected = false;

// Introduction on HID report descriptor can be found on https://eleccelerator.com/tutorial-about-usb-hid-report-descriptors/
// Full specificiations can be found in the USB official document (Device Class Definition for Human Interface Devices (HID)) on https://usb.org/sites/default/files/hid1_11.pdf
const uint8_t hidReportDescriptor[] = {
  // Mouse descriptor
  0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
  0x09, 0x02,        // Usage (Mouse)
  0xA1, 0x01,        // Collection (Application)
  0x85, 0x01,        //     Report ID (1)
  0x09, 0x01,        //   Usage (Pointer)
  0xA1, 0x00,        //   Collection (Physical)
  // Set buttons (first 3 bits)
  0x05, 0x09,        //     Usage Page (Button)
  0x19, 0x01,        //     Usage Minimum (Button 1)
  0x29, 0x03,        //     Usage Maximum (Button 3)
  0x15, 0x00,        //     Logical Minimum (0)
  0x25, 0x01,        //     Logical Maximum (1)
  0x95, 0x03,        //     Report Count (3)
  0x75, 0x01,        //     Report Size (1)
  0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  // Padding (5 bits to make a byte 0)
  0x95, 0x01,        //     Report Count (1)
  0x75, 0x05,        //     Report Size (5)
  0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  // Mouse movement. Combine the X and Y together to save memory
  0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
  0x09, 0x30,        //     Usage (X)
  0x09, 0x31,        //     Usage (Y)
  0x15, 0x81,        //     Logical Minimum (-127)
  0x25, 0x7F,        //     Logical Maximum (127)
  0x75, 0x08,        //     Report Size (8)
  0x95, 0x02,        //     Report Count (2)
  0x81, 0x06,        //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
  0xC0,              //   End Collection
  0xC0               // End Collection
};

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      Serial.println("A device is connecting to the ESP32");

      // Restart advertising
      BLEDevice::startAdvertising();
    };

    void onDisconnect(BLEServer* pServer) {
      Serial.println("A device has been disconnected from the ESP32");
    }  
};

void setupBleTask(void *) {
  // Create the BLE Device
  BLEDevice::init("ESP32 Mouse");

  // Create the BLE Server
  pServer = BLEDevice::createServer();

  // Set the callback for when a client connect / disconnect
  pServer->setCallbacks(new MyServerCallbacks());

  // Create a bluetooth low energy human interface device
  hid = new BLEHIDDevice(pServer);

  // Set manufacturer name
  hid->manufacturer()->setValue("Kelderro");

  // Set the vendor ID, product ID and Product version (https://www.bluetooth.com/wp-content/uploads/Sitecore-Media-Library/Gatt/Xml/Characteristics/org.bluetooth.characteristic.pnp_id.xml)
  hid->pnp(0x02, 0xe502, 0xa111, 0x0210);

  // Setting the RemoteWake and NormallyConnectable values (https://www.bluetooth.com/wp-content/uploads/Sitecore-Media-Library/Gatt/Xml/Characteristics/org.bluetooth.characteristic.hid_information.xml)
  hid->hidInfo(0x00, 0x02);

  hid->reportMap((uint8_t*)hidReportDescriptor, sizeof(hidReportDescriptor));

  hid->startServices();

  // Start advertising
  pAdvertising = pServer->getAdvertising();
  pAdvertising->setAppearance(HID_MOUSE);
  pAdvertising->addServiceUUID(hid->hidService()->getUUID());

  pAdvertising->start();

  // Remove task from RTOS kernels management
  vTaskDelete(NULL);
}

void moveMousePointerTask(void *) {
  const TickType_t xDelay = (10 * 1000) / portTICK_PERIOD_MS;

  for(;;) { // infinite loop
    Serial.println("Moving mouse!");
    
    // Pause the task again for 10 seconds
    vTaskDelay(xDelay);
  }
}

void setup() {
  Serial.begin(115200);

  xTaskCreate(setupBleTask, "Setup BLE", 20000, NULL, 5, NULL);
  xTaskCreate(moveMousePointerTask, "Move mouse pointer", 1000, NULL, 1, NULL);
}

void loop() {
  delay(1000);
}
