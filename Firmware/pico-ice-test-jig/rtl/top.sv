module top (
  input ICE_2,
  input ICE_3,
  input ICE_4,
  input ICE_6,
  input ICE_9,
  input ICE_10,
  input ICE_11,
  input ICE_18,
  input ICE_19,
  input ICE_20_G3,
  input ICE_21,
  input ICE_23,
  input ICE_25,
  input ICE_26,
  input ICE_27,
  input ICE_28,
  input ICE_31,
  input ICE_32,
  input ICE_34,
  input ICE_35_G0,
  input ICE_36,
  input ICE_38,
  input ICE_42,
  input ICE_43,
  input ICE_44_G6,
  input ICE_45,
  input ICE_46,
  input ICE_47,
  input ICE_48,
  input ICE_FLASH_IO2,
  input ICE_FLASH_IO3,
  input ICE_SO,
  input ICE_SI,
  input ICE_SCK,
  input ICE_SSN,
  input SRAM_SS,
  output LED_G,
  output LED_B,
  output LED_R
);
  logic led_r = ICE_10;

  SB_RGBA_DRV #(
    .CURRENT_MODE ("0i1"),      // half current
    .RGB0_CURRENT ("0i000001"), // 4 mA
    .RGB1_CURRENT ("0i000001"), // 4 mA
    .RGB2_CURRENT ("0i000001")  // 4 mA
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
  logic ICE_31 = ICE_13;
  logic ICE_32 = ICE_28;
  logic ICE_38 = ICE_32;
  logic ICE_42 = ICE_36;
  logic ICE_35 = ICE_43;
  logic ICE_11 = ICE_37;
  logic ICE_9  = ICE_6;

  //     │       │
  // ICE_44█───█ICE_45 (1i)
  //     │ :     │
  // ICE_46█───█ICE_47
  //     │     : │
  // ICE_48█───█ICE_2
  //     │ :     │
  //  ICE_3█───█ICE_4 (1o)
  //     ├───────┘
  logic ICE_46 = ICE_44;
  logic ICE_2  = ICE_47;
  logic ICE_3  = ICE_48;

  //                   │
  //  (3i) ICE_16█───█ICE_14
  //                 : │
  //  (3o) ICE_17█───█ICE_15
  //           ┌───────┤
  logic ICE_15 = ICE_14;

  //           ┌───────┤
  //  (0o) ICE_27█   █ICE_26 (0i)
  //           │       │
  //  (1o) ICE_25█   █ICE_23 (1i)
  //           │       │
  //  (2o) ICE_21█   █ICE_20 (2i)
  //           │       │
  //  (3o) ICE_19█   █ICE_18 (3i)
  //           │       │
  logic ICE_27 = ICE_10, ICE_12 = ICE_26;
  logic ICE_25 = ICE_4,  ICE_45 = ICE_23;
  // Driven by the RP2040
  logic ICE_19 = ICE_17, ICE_16 = ICE_18;

endmodule
