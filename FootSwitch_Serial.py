import serial
import time
import threading
# シリアルポートの設定
# port = "/dev/tty.usbmodem142301"  # この部分は実際の環境に合わせて変更してください
port = "COM4"
baudrate = 9600        # ボーレート（デバイスに合わせて設定）
class Serial2Joy:
    def __init__(self):
        self.ser = serial.Serial(port, baudrate, timeout=1)
        print(f"Connected to {self.ser.name}")
        self.running = True
        self.state = 0
        self.thread = threading.Thread(target=self.run)
        self.thread.start()
    def run(self):
        while self.running:
            # データが利用可能かチェック
            if self.ser.in_waiting > 0:
                # データを読み取る
                data = self.ser.readline().decode('utf-8').strip()
                # print(f"Received: {data}")
                if "0" in data:
                    self.state = 0
                elif "1" in data:
                    self.state = 1
                # print(f"State: {self.state}")
    def publish(self):
        print(f"State: {self.state}")
    def exit(self):
        self.running = False
        self.thread.join()
        self.ser.close()
if __name__ == "__main__":
    s2j = Serial2Joy()
    try:
        while True:
            s2j.publish()
            time.sleep(0.1)
    except KeyboardInterrupt:
        print("KeyboardInterrupt")
        s2j.exit()