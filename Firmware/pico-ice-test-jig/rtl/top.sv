module top (
  output  ICE_2,
  output  ICE_3,
  input   ICE_4,
  input   ICE_6,
  output  ICE_9,
  input   ICE_10,
  output  ICE_11,
  output  ICE_12,
  input   ICE_13,
  input   ICE_14,
  output  ICE_15,
  output  ICE_16,
  input   ICE_17,
  input   ICE_18,
  output  ICE_19,
  output  ICE_20,
  input   ICE_21,
  input   ICE_23,
  output  ICE_25,
  input   ICE_26,
  output  ICE_27,
  input   ICE_28,
  output  ICE_31,
  output  ICE_32,
  input   ICE_34,
  output  ICE_35,
  input   ICE_36,
  input   ICE_37,
  output  ICE_38,
  output  ICE_42,
  input   ICE_43,
  input   ICE_44,
  output  ICE_45,
  output  ICE_46,
  input   ICE_47,
  input   ICE_48,
  output  LED_R,
  output  LED_G,
  output  LED_B
);

  // keep all signals high-impedance when this is up
  logic reset_pin_i;

  // logic output signal to drive from something else
  logic ICE_2_o, ICE_3_o, ICE_9_o, ICE_11_o, ICE_12_o, ICE_15_o, ICE_16_o;
  logic ICE_19_o, ICE_25_o, ICE_27_o, ICE_31_o, ICE_32_o, ICE_35_o;
  logic ICE_38_o, ICE_42_o, ICE_45_o, ICE_46_o;

  // turn the LED white when pushing a button
  logic led_r;
  logic led_g;
  logic led_b;

  SB_RGBA_DRV #(
    .CURRENT_MODE ("0b1"),   /* half current */
    .RGB0_CURRENT ("0b000001"),  /* 4 mA */
    .RGB1_CURRENT ("0b000001"),  /* 4 mA */
    .RGB2_CURRENT ("0b000001") /* 4 mA */
  ) rgba_drv (
    .CURREN(1'b1),
    .RGBLEDEN(1'b1),
    .RGB0PWM(led_g),
    .RGB0(LED_G),
    .RGB1PWM(led_b),
    .RGB1(LED_B),
    .RGB2PWM(led_r),
    .RGB2(LED_R)
  );

  assign led_r = !ICE_10;
  assign led_g = !ICE_10;
  assign led_b = !ICE_10 | reset_pin_i;

  SB_IO #(
    .PIN_TYPE(6'b1010_01),
    .PULLUP(1'b0)
  ) output_pins [16:0] (
    .PACKAGE_PIN({
      ICE_2, ICE_3, ICE_9, ICE_11, ICE_12, ICE_15, ICE_16,
      ICE_19, ICE_25, ICE_27, ICE_31, ICE_32, ICE_35, ICE_38,
      ICE_42, ICE_45, ICE_46
    }),
    .OUTPUT_ENABLE({17{!reset_pin_i}}),
    .D_OUT_0({
      ICE_2_o, ICE_3_o, ICE_9_o, ICE_11_o, ICE_12_o, ICE_15_o, ICE_16_o,
      ICE_19_o, ICE_25_o, ICE_27_o, ICE_31_o, ICE_32_o, ICE_35_o, ICE_38_o,
      ICE_42_o, ICE_45_o, ICE_46_o
    })
  );

  // In the diagrams below:
  // 'i'nput means data coming into the pin chain, driven by the RP2040
  // 'o'utput means data going out of the pin chain, read by the RP2040

  //           │       │
  // (rst) ICE_21█   █ICE_20 (button mirrored)
  //           │       │
  assign ICE_20 = ICE_10;
  assign reset_pin_i = ICE_21;

  //     │(0i)
  // ICE_12█   █
  //     │ │ .......
  // ICE_13█'  █   :
  //     ├───────┐ :
  //     │ █   █ │ :
  //     │       │ :
  //     │ █   █ │ :
  //     │       │ :
  // ICE_28█───█ICE_31
  //     │ :     │
  // ICE_32█───█ICE_34
  //     │     : │
  // ICE_36█───█ICE_38
  //     │ :     │
  // ICE_42█───█ICE_43
  //     ├─────:─┤
  // ICE_37█───█ICE_35
  //     │ :
  // ICE_11█───█ICE_6
  //     │     :
  // ICE_10█───█ICE_9
  //  PB │(0o)
  assign ICE_31_o = ICE_13;
  assign ICE_32_o = ICE_28;
  assign ICE_38_o = ICE_34;
  assign ICE_42_o = ICE_36;
  assign ICE_35_o = ICE_43;
  assign ICE_11_o = ICE_37;
  assign ICE_9_o  = ICE_6;

  //     │       │
  // ICE_44█───█ICE_45 (1i)
  //     │ :     │
  // ICE_46█───█ICE_47
  //     │     : │
  // ICE_48█───█ICE_2
  //     │ :     │
  //  ICE_3█───█ICE_4 (1o)
  //     ├───────┘
  assign ICE_46_o = ICE_44;
  assign ICE_2_o  = ICE_47;
  assign ICE_3_o  = ICE_48;

  //                   │
  //  (2i) ICE_16█───█ICE_14
  //                 : │
  //  (2o) ICE_17█───█ICE_15
  //           ┌───────┤
  assign ICE_15_o = ICE_14;

  //           ┌───────┤
  //  (0o) ICE_25█   █ICE_23 (0i)
  //           │       │
  //  (1o) ICE_19█   █ICE_18 (1i)
  //           │       │
  //  (2o) ICE_27█   █ICE_26 (2i)
  //           │       │
  assign ICE_25_o = ICE_10, ICE_12_o = ICE_23;
  assign ICE_19_o = ICE_4,  ICE_45_o = ICE_18;
  assign ICE_27_o = ICE_17, ICE_16_o = ICE_26;

endmodule
