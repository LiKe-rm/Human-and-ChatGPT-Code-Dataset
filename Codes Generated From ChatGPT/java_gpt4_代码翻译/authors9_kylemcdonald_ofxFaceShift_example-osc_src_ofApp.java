import oscP5.*;
import netP5.*;
import processing.core.PApplet;
import processing.core.PVector;
import processing.data.XML;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class ofApp extends PApplet {
  String oscHost;
  int oscPort;
  int faceShiftPort;
  float lastPacket;
  long timer;

  ArrayList<String> addresses = new ArrayList<>();

  OscP5 osc;
  NetAddress remote;

  public static void main(String[] args) {
    PApplet.main("ofApp");
  }

  public void settings() {
    size(400, 200);
  }

  public void setup() {
    frameRate(120);
    loadSettings();
    timer = System.currentTimeMillis();
    osc = new OscP5(this, oscPort);
    remote = new NetAddress(oscHost, oscPort);
  }

  public void draw() {
    float status = map(System.currentTimeMillis() - timer, 0, 3000, 0, 1, true);
    int magentaPrint = color(236, 0, 140);
    background(lerpColor(color(128), magentaPrint, status));
    fill(255);
    text("Listening on " + faceShiftPort + " at " + frameRate + " packets/second", 10, 20);
    text("Sending to " + oscHost + ":" + oscPort, 10, 40);
    if (status == 1) {
      text("Not receiving any packets.", 10, 60);
    }
  }

  void loadSettings() {
    XML xml = loadXML("settings.xml");
    XML oscSettings = xml.getChild("osc");
    oscHost = oscSettings.getString("host", "localhost");
    oscPort = oscSettings.getInt("port", 8338);

    XML faceShiftSettings = xml.getChild("faceShift");
    faceShiftPort = faceShiftSettings.getInt("port", 33433);

    try (BufferedReader br = new BufferedReader(new FileReader("addresses.txt"))) {
      String line;
      while ((line = br.readLine()) != null) {
        addresses.add(line);
      }
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  void sendBundle(ArrayList<OscMessage> bundle) {
    for (OscMessage msg : bundle) {
      osc.send(msg, remote);
    }
  }

  void addMessage(ArrayList<OscMessage> bundle, String address, float data) {
    OscMessage msg = new OscMessage(address);
    msg.add(data);
    bundle.add(msg);
  }

  void addMessage(ArrayList<OscMessage> bundle, String address, int data) {
    OscMessage msg = new OscMessage(address);
    msg.add(data);
    bundle.add(msg);
  }

  void addMessage(ArrayList<OscMessage> bundle, String address, PVector data) {
    OscMessage msg = new OscMessage(address);
    msg.add(data.x);
    msg.add(data.y);
    msg.add(data.z);
    bundle.add(msg);
  }
}
