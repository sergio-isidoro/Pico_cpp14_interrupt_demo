# ⚙️ Raspberry Pi Pico LED Blinker with EXTI Interrupts (C++14 · Wokwi Compatible)

A modern, C++14-based project using the **Pico SDK** on the **Raspberry Pi Pico**, where two LEDs blink with different intervals — and a button connected via an **interrupt (EXTI)** toggles the pause/resume state of both LEDs in real time.

- 🔃 Non-blocking LED blinking using `sleep_ms`
- 🧠 Hardware interrupt (EXTI) for responsive button control
- ⚡ Ultra-fast pause/resume toggle on GPIO falling edge
- 🖥️ Output via `stdio` for debugging (Wokwi terminal)

> 🔧 The project uses `gpio_set_irq_enabled_with_callback` to handle button input via interrupt, ensuring efficient and responsive control without polling.

---

## 📋 Features

- 🌈 **Two Independent LEDs**:
  - **LED1 (GPIO0)**: blinks every **0.5s**
  - **LED2 (GPIO1)**: blinks every **0.25s**
- 🔘 **Button (GPIO2)**:
  - Triggers a **falling edge interrupt** (EXTI) to pause/resume blinking
- 🚀 **Fully compatible with Wokwi Simulator**
- 🧱 **Minimal C++14 code using `pico-sdk`**
- 🧠 **Uses `std::atomic`** to safely share state between main loop and ISR
- ✅ **Efficient & responsive** without blocking or polling

---

## 🛠️ Requirements

- A Raspberry Pi Pico board (real or simulated)
- 2 LEDs connected to:
  - **GPIO0** (LED1)
  - **GPIO1** (LED2)
- 1 Button connected to:
  - **GPIO2** (active-low with pull-up resistor)
- Pull-up resistor for the button (or internal pull-up)
- Wokwi account (optional, for online simulation)

---

## 🔩 Pin Configuration

| Device | GPIO Pin |
|--------|----------|
| LED1   | GPIO0    |
| LED2   | GPIO1    |
| Button | GPIO2    |

> Pins can be easily changed by editing the `LED1_PIN`, `LED2_PIN`, and `BUTTON_PIN` constants in `main.cpp`.

---

## 🧪 Behavior Overview

- On boot:
  - LED1 starts blinking at 0.5s intervals
  - LED2 blinks faster (0.25s intervals)
- Pressing the button on GPIO2:
  - Triggers an **interrupt**
  - Toggles the `paused` flag (`true` ⇄ `false`)
  - When paused, both LEDs turn off and stay off
  - When resumed, blinking resumes at their original rates
- Real-time messages printed to `stdio` console (Wokwi terminal)


---

## 💡 Example: `gpio_callback` Function

```cpp
void gpio_callback(uint gpio, uint32_t events) {
    if (gpio == BUTTON_PIN && (events & GPIO_IRQ_EDGE_FALL)) {
        paused = !paused;
        std::cout << (paused ? "PAUSED\n" : "RESUMED\n");
    }
}
```

