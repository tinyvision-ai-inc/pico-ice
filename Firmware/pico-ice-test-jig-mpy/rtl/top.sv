module top (
  input   ICE_2,
  input   ICE_3,
  output  ICE_4,
  input   ICE_6,
  output  ICE_9,
  input   ICE_10,
  output  ICE_11,
  input   ICE_12,
  output  ICE_13,
  input   ICE_14,
  output  ICE_15,
  output  ICE_16,
  input   ICE_17,
  output  ICE_18,
  input   ICE_19,
  input   ICE_20,
  output  ICE_21,
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
  output  ICE_44,
  input   ICE_45,
  input   ICE_46,
  output  ICE_47,
  output  ICE_48,

  output  LED_G,
);

  // logic output signal to drive from something else
  logic ICE_4_o, ICE_9_o, ICE_11_o, ICE_13_o, ICE_15_o, ICE_16_o, ICE_18_o;
  logic ICE_25_o, ICE_27_o, ICE_31_o, ICE_32_o, ICE_35_o, ICE_38_o, ICE_42_o;
  logic ICE_44_o, ICE_47_o, ICE_48_o;

  // signals
  logic high_z;

  // turn the LED white when pushing a button

  SB_RGBA_DRV #(
    .CURRENT_MODE("0b1"),       // half current
    .RGB0_CURRENT("0b000001"),  // 4 mA
    .RGB1_CURRENT("0b000001"),  // 4 mA
    .RGB2_CURRENT("0b000001")   // 4 mA
  ) rgba_drv (
    .CURREN(1'b1),
    .RGBLEDEN(1'b1),
    .RGB0(LED_G), .RGB0PWM(high_z),
  );

  SB_IO #(
    .PIN_TYPE(6'b1010_01),
    .PULLUP(1'b0)
  ) output_pins [16:0] (
    .OUTPUT_ENABLE(
      !high_z
    ),
    .PACKAGE_PIN({
      ICE_4, ICE_9, ICE_11, ICE_13, ICE_15, ICE_16, ICE_18,
      ICE_25, ICE_27, ICE_31, ICE_32, ICE_35, ICE_38, ICE_42,
      ICE_44, ICE_47, ICE_48
    }),
    .D_OUT_0({
      ICE_4_o, ICE_9_o, ICE_11_o, ICE_13_o, ICE_15_o, ICE_16_o, ICE_18_o,
      ICE_25_o, ICE_27_o, ICE_31_o, ICE_32_o, ICE_35_o, ICE_38_o, ICE_42_o,
      ICE_44_o, ICE_47_o, ICE_48_o
    })
  );

  // pin chain
  //    │   ......................
  //    │ .'                      '.     │
  //ICE_12█   █              ICE_16█───█ICE_14
  //    │ │                            : │
  //ICE_13█   █              ICE_17█───█ICE_15
  //    ├──:────┐                ┌─:─────┤
  //    │ █:  █ │            ICE_25█───█ICE_23
  //    │  :    │                │     : │
  //    │ █:  █ │            ICE_19█───█ICE_18
  //    │  :    │                │ :     │
  //ICE_28█───█ICE_31     <--ICE_27█   █ICE_26<--
  //    │     : │                │    .' │
  //ICE_32█───█ICE_34    btn/ICE_21█.' █ICE_20/high-z
  //    │ :     │                │.'     │
  //ICE_36█───█ICE_38           .'
  //    │     : │             .'
  //ICE_42█───█ICE_43       .'
  //    ├─:─────┘         .'
  //ICE_37█───█ICE_35   .'
  //    │     :        :
  //ICE_11█───█ICE_6   :
  //    │ :            :
  //ICE_10█───█ICE_9   :
  // PB ├────:──┐      :
  //    │ █  :█ │      :
  //    │    :  │      :
  //    │ █  :█ │      :
  //    │    :  │      :
  //ICE_44█───█ICE_45  :
  //    │ :     │      :
  //ICE_46█───█ICE_47  :
  //    │     : │      :
  //ICE_48█───█ICE_2   :
  //    │ :     │    .'
  // ICE_3█───█ICE_4'
  //    ├───────┘
  assign ICE_4_o  = ICE_26;
  assign ICE_48_o = ICE_3;
  assign ICE_47_o = ICE_2;
  assign ICE_44_o = ICE_46;
  assign ICE_9_o  = ICE_45;
  assign ICE_11_o = ICE_10;
  assign ICE_35_o = ICE_6;
  assign ICE_42_o = ICE_37;
  assign ICE_38_o = ICE_43;
  assign ICE_32_o = ICE_36;
  assign ICE_31_o = ICE_34;
  assign ICE_13_o = ICE_28;
  assign ICE_16_o = ICE_12;
  assign ICE_15_o = ICE_14;
  assign ICE_25_o = ICE_17;
  assign ICE_18_o = ICE_23;
  assign ICE_27_o = ICE_19;

  // button forwarding
  assign ICE_21 = ICE_10;

  // signal from the RP2040
  assign high_z = ICE_20;

endmodule
