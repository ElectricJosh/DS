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

            string iotHubUri = "ElectricJosh.azure-devices.net";
            string deviceKey = "q+LyxuvjoEnaEn4DVWSClfO0vX2p3F0mQwt4dbrXKbA=";
            string deviceId = "AAs1qKYBsj2inp%2bha0RWjozirQkjYJDrAuk3WEaP1K7zpw%3d%3d";

            var deviceClient = DeviceClient.Create(iotHubUri,
                    AuthenticationMethodFactory.
                        CreateAuthenticationWithRegistrySymmetricKey(deviceId, deviceKey),
                    TransportType.Http1);

            var str = "Hello, Cloud!";
            var message = new Message(Encoding.UTF8.GetBytes(str));

            message.ContentEncoding = "utf-8";
            message.ContentType = "application/json";

            await deviceClient.SendEventAsync(message);
        }
    }
}
