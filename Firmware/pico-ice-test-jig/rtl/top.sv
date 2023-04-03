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
  input   ICE_20,
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
  input   ICE_48
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
  assign ICE_31 = ICE_13;
  assign ICE_32 = ICE_28;
  assign ICE_38 = ICE_32;
  assign ICE_42 = ICE_36;
  assign ICE_35 = ICE_43;
  assign ICE_11 = ICE_37;
  assign ICE_9  = ICE_6;

  //     │       │
  // ICE_44█───█ICE_45 (1i)
  //     │ :     │
  // ICE_46█───█ICE_47
  //     │     : │
  // ICE_48█───█ICE_2
  //     │ :     │
  //  ICE_3█───█ICE_4 (1o)
  //     ├───────┘
  assign ICE_46 = ICE_44;
  assign ICE_2  = ICE_47;
  assign ICE_3  = ICE_48;

  //                   │
  //  (3i) ICE_16█───█ICE_14
  //                 : │
  //  (3o) ICE_17█───█ICE_15
  //           ┌───────┤
  assign ICE_15 = ICE_14;

  //           ┌───────┤
  //  (0o) ICE_27█   █ICE_26 (0i)
  //           │       │
  //  (1o) ICE_25█   █ICE_23 (1i)
  //           │       │
  //  (2o) ICE_21█   █ICE_20 (2i)
  //           │       │
  //  (3o) ICE_19█   █ICE_18 (3i)
  //           │       │
  assign ICE_27 = ICE_10, ICE_12 = ICE_26;
  assign ICE_25 = ICE_4,  ICE_45 = ICE_23;
  // Driven by the RP2040
  assign ICE_19 = ICE_17, ICE_16 = ICE_18;

endmodule
