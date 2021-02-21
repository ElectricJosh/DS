package com.example.josh.watermeter;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.Handler;
import android.os.Message;
import android.provider.Settings;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

import static android.bluetooth.BluetoothDevice.BOND_BONDED;

public class Main extends AppCompatActivity {

    char ResponseModeByte;
    BluetoothAdapter BTadapter;
    BluetoothSocket BTsock;

    TextView DebugXML;
    TextView WaterFlowXML;
    TextView IsoStatusXML;
    TextView IsoErrorXML;
    TextView NodeErrorXML;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

        WaterFlowXML = (TextView) findViewById(R.id.WaterFlowText);
        IsoStatusXML = (TextView) findViewById(R.id.IsolatorText);
        IsoErrorXML = (TextView) findViewById(R.id.IsolatorErrorCodeText);
        NodeErrorXML = (TextView) findViewById(R.id.NodeErrorCodeText);
        DebugXML = (TextView) findViewById(R.id.DebugText);

        WaterFlowXML.setText(R.string.FlowString);
        IsoStatusXML.setText(R.string.IsolatorStatus);
        IsoErrorXML.setText(R.string.IsolatorError);
        NodeErrorXML.setText(R.string.NodeError);
        DebugXML.setText(R.string.DebugDefault);

        ResponseModeByte = 'A'; // A // starts in normal mode
    }

    Thread BT_Thread = new Thread() // this is just an elaborate timing thread
    {
        @Override
        public void run() {
            while (true) {
                try {
                    BTUpdateHandler.obtainMessage(0).sendToTarget();
                    Thread.sleep(2500);
                } catch (Exception e) {
                    DebugXML.setText(e.toString());
                }
            }
        }
    };

    @SuppressLint("HandlerLeak")
    Handler BTUpdateHandler = new Handler() {
        @Override
        public void handleMessage(Message message) {
            try {
                DebugXML.setText("Handling Message");
                InputStream BTStreamIn = BTsock.getInputStream();
                OutputStream BTStreamOut = BTsock.getOutputStream();
                if (BTsock.isConnected()) {
                    DebugXML.setText("Connected to socket");
                    if (BTStreamIn.available() > 5)
                    {
                        DebugXML.setText("Read data available");
                        byte[] RXData = {0,0,0,0,0,0};
                        for(int J = 0; J < RXData.length; J++)
                        {
                            RXData[J] =  (byte)BTStreamIn.read();
                        }
                        short FlowRate = 0;
                        FlowRate |= RXData[0];
                        FlowRate |= ((RXData[1]) << 8);
                        float FloatFlowRate = (float)FlowRate/100.0f;
                        WaterFlowXML.setText(R.string.FlowString);
                        WaterFlowXML.append(String.valueOf(FloatFlowRate));
                        WaterFlowXML.append(" L/min");

                        byte IsolationStatus = RXData[2];
                        IsoStatusXML.setText(R.string.IsolatorStatus);
                        if (IsolationStatus == 0x00) // active and no errors
                        {
                            IsoStatusXML.append("Water Enabled");
                            IsoErrorXML.setText(R.string.IsolatorError);
                            IsoErrorXML.append(String.valueOf(IsolationStatus));
                        } else // active with error code
                        {
                            IsoStatusXML.append("Water Disabled");
                            IsoErrorXML.setText(R.string.IsolatorError);
                            IsoErrorXML.append(String.valueOf(IsolationStatus));
                        }

                        short LatestErrorNodeID = 0;
                        LatestErrorNodeID |= RXData[3];
                        LatestErrorNodeID |= ((RXData[4] & 0x07) << 8); // 11 bit ID
                        byte LatestErrorNodeData = RXData[5];

                        NodeErrorXML.setText(R.string.NodeError);
                        NodeErrorXML.append(String.valueOf(LatestErrorNodeID) + "_" + String.valueOf(LatestErrorNodeData));

                        while (BTStreamIn.available() > 0) // clear buffer in case of backlogs
                        {
                            BTStreamIn.read();
                        }
                    } else // request current data
                    {
                        DebugXML.setText("Transmit request");
                        BTStreamOut.write(ResponseModeByte); // request data from the main board
                        ResponseModeByte = 'A'; // reset to normal update mode after oneshot request
                    }
                }
            } catch (Exception e) {
                DebugXML.setText(e.toString());
            }
        }
    };

    public void Bluetooth_Settings_XML(View view) {
        try {
            if (BTadapter == null) {
                BTadapter = BluetoothAdapter.getDefaultAdapter();
                return;
            }
            if (!BTadapter.isEnabled()) // Because we are using intents I cannot run two sequentially.
            {
                DebugXML.setText("Intent");
                startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), 0);
                return;
            } else {
                startActivityForResult(new Intent(Settings.ACTION_BLUETOOTH_SETTINGS), 0);
                return;
            }
        } catch (Exception x) {
            DebugXML.setText(x.toString());
        }
    }

    public void Bluetooth_Connect_XML(View view) {
        try {
            if (BTadapter == null) {
                DebugXML.setText("Adapter is not initialised or supported");
                BTadapter = BluetoothAdapter.getDefaultAdapter();
            }
            Set<BluetoothDevice> pairedDevices = BTadapter.getBondedDevices();
            BluetoothDevice PairedDevice = null;
            if (pairedDevices.size() > 0) {
                for (BluetoothDevice device : pairedDevices) {
                    if (device.getBondState() == BOND_BONDED) {
                        PairedDevice = device;
                        break;
                    }
                }
            } else {
                DebugXML.setText("No Connected Devices");
                return;
            }
            UUID DeviceID = PairedDevice.getUuids()[0].getUuid();
            BTsock = PairedDevice.createRfcommSocketToServiceRecord(DeviceID); // secure
            //BTsock = PairedDevice.createInsecureRfcommSocketToServiceRecord(DeviceID); // insecure alternative
            BTsock.connect();
            BT_Thread.start();
            DebugXML.setText("Connected");
        } catch (Exception e) {
            DebugXML.setText(e.toString());
            return;
        }
    }

    public void ActivateIsolator_XML(View view) {
        DebugXML.setText("Isolator Activated");
        ResponseModeByte = 'B';
    }

    public void DeactivateIsolator_XML(View view) {
        DebugXML.setText("Isolator Deactivated");
        ResponseModeByte = 'C';
    }
}
