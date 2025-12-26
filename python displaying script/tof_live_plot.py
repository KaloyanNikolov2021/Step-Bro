import serial
import matplotlib.pyplot as plt
import collections
import time
import statistics

# ---- Настройки ----
PORT = "COM4"       # смени ако е друг
BAUD = 115200
MAX_POINTS = 200    # брой точки на графиката

# ---- Serial ----
ser = serial.Serial(PORT, BAUD, timeout=1)

# ---- Декове за данни ----
data = collections.deque(maxlen=MAX_POINTS)
timestamps = collections.deque(maxlen=MAX_POINTS)

min_val = None
max_val = None

# ---- Настройки на графиката ----
plt.style.use('dark_background')
plt.ion()
fig, ax = plt.subplots(figsize=(25, 12))
start_time = time.time()

while True:
    try:
        line = ser.readline().decode().strip()
        if not line:
            continue

        # CSV: time_ms,distance,status
        t_ms, dist, status = map(int, line.split(","))

        if status != 0:
            continue  # филтрираме невалидните измервания

        data.append(dist)
        timestamps.append(t_ms / 1000.0)

        # Calculate statistics
        avg = statistics.mean(data) if data else 0
        stdev = statistics.stdev(data) if len(data) > 1 else 0

        # min / max
        min_val = dist if min_val is None else min(min_val, dist)
        max_val = dist if max_val is None else max(max_val, dist)

        # --- Чистене и чертане ---
        ax.clear()
        ax.plot(timestamps, data, label="Distance (mm)", color='cyan')
        ax.set_xlabel("Time (s)")
        ax.set_ylabel("Distance (mm)")
        ax.set_ylim(0, 2000)
        ax.grid(True)
        ax.set_title("VL53L4CD Live Distance")

        # --- Статистика на графиката ---
        ax.text(0.02, 0.95, f"Current: {dist} mm", transform=ax.transAxes)
        ax.text(0.02, 0.90, f"Min: {min_val} mm", transform=ax.transAxes)
        ax.text(0.02, 0.85, f"Max: {max_val} mm", transform=ax.transAxes)
        ax.text(0.02, 0.80, f"Avg: {avg:.1f} mm", transform=ax.transAxes)
        ax.text(0.02, 0.75, f"Std Dev: {stdev:.1f} mm", transform=ax.transAxes)
        ax.text(0.02, 0.70, f"Samples: {len(data)}", transform=ax.transAxes)

        plt.pause(0.01)

    except Exception as e:
        print("Error:", e)
