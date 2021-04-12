using Windows.UI.Xaml.Controls;

using Microsoft.Azure.Devices.Client;
using System.Text;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace AzureTest
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            SendDeviceToCloudMessagesAsync();
        }

        static async void SendDeviceToCloudMessagesAsync()
        {

            string IoTHubHostName = ""; // Azure IoT Hub Hostname
            string DevicePrimaryKey = ""; // Device Primary Key
            string DeviceID = ""; // Device ID or Name

            var deviceClient = DeviceClient.Create(IoTHubHostName,
                    AuthenticationMethodFactory.
                        CreateAuthenticationWithRegistrySymmetricKey(DeviceID, DevicePrimaryKey),
                    TransportType.Http1);

            var str = "Hello, Cloud!";
            var message = new Message(Encoding.UTF8.GetBytes(str));

            message.ContentEncoding = "utf-8";
            message.ContentType = "application/json";

            await deviceClient.SendEventAsync(message);
        }
    }
}
