% This is an interface specification for the Mathwork's Embedded Coder C code generator.
%
% This file has been created with comFramework - codeGenerator version 1.10.4,
% see http://sourceforge.net/projects/comframe/
%
% The interface is generated from these network database files:
%   CAN_RT_attributed.dbc

%
% CAN Bus PT
%

% Received Frames

% Frame RT_SB_INS_Vel_Body_Axes, 215 (0x0d7)
% Signal crt_PT_0d7_Validity_INS_Vel_Forwards
crt_PT_0d7_Validity_INS_Vel_Forwards = Simulink.Signal;
crt_PT_0d7_Validity_INS_Vel_Forwards.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_0d7_Validity_INS_Vel_Forwards.RTWInfo.Alias = '';
crt_PT_0d7_Validity_INS_Vel_Forwards.Description = ...
  ['Frame: RT_SB_INS_Vel_Body_Axes, 215 (0x0d7).' char(10) ...
   'Signal: Validity_INS_Vel_Forwards.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_0d7_Validity_INS_Vel_Forwards.DataType = 'boolean';
crt_PT_0d7_Validity_INS_Vel_Forwards.Min = 0.0;
crt_PT_0d7_Validity_INS_Vel_Forwards.Max = 1.0;
crt_PT_0d7_Validity_INS_Vel_Forwards.DocUnits = '';
crt_PT_0d7_Validity_INS_Vel_Forwards.Dimensions = 1;
crt_PT_0d7_Validity_INS_Vel_Forwards.Complexity = 'real';
crt_PT_0d7_Validity_INS_Vel_Forwards.SampleTime = -1;
crt_PT_0d7_Validity_INS_Vel_Forwards.SamplingMode = 'Sample based';
crt_PT_0d7_Validity_INS_Vel_Forwards.InitialValue = '';
% Signal crt_PT_0d7_Validity_INS_Vel_Sideways
crt_PT_0d7_Validity_INS_Vel_Sideways = Simulink.Signal;
crt_PT_0d7_Validity_INS_Vel_Sideways.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_0d7_Validity_INS_Vel_Sideways.RTWInfo.Alias = '';
crt_PT_0d7_Validity_INS_Vel_Sideways.Description = ...
  ['Frame: RT_SB_INS_Vel_Body_Axes, 215 (0x0d7).' char(10) ...
   'Signal: Validity_INS_Vel_Sideways.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_0d7_Validity_INS_Vel_Sideways.DataType = 'boolean';
crt_PT_0d7_Validity_INS_Vel_Sideways.Min = 0.0;
crt_PT_0d7_Validity_INS_Vel_Sideways.Max = 1.0;
crt_PT_0d7_Validity_INS_Vel_Sideways.DocUnits = '';
crt_PT_0d7_Validity_INS_Vel_Sideways.Dimensions = 1;
crt_PT_0d7_Validity_INS_Vel_Sideways.Complexity = 'real';
crt_PT_0d7_Validity_INS_Vel_Sideways.SampleTime = -1;
crt_PT_0d7_Validity_INS_Vel_Sideways.SamplingMode = 'Sample based';
crt_PT_0d7_Validity_INS_Vel_Sideways.InitialValue = '';
% Signal crt_PT_0d7_Bit4
crt_PT_0d7_Bit4 = Simulink.Signal;
crt_PT_0d7_Bit4.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_0d7_Bit4.RTWInfo.Alias = '';
crt_PT_0d7_Bit4.Description = ...
  ['Frame: RT_SB_INS_Vel_Body_Axes, 215 (0x0d7).' char(10) ...
   'Signal: Bit4.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_0d7_Bit4.DataType = 'boolean';
crt_PT_0d7_Bit4.Min = 0.0;
crt_PT_0d7_Bit4.Max = 1.0;
crt_PT_0d7_Bit4.DocUnits = '';
crt_PT_0d7_Bit4.Dimensions = 1;
crt_PT_0d7_Bit4.Complexity = 'real';
crt_PT_0d7_Bit4.SampleTime = -1;
crt_PT_0d7_Bit4.SamplingMode = 'Sample based';
crt_PT_0d7_Bit4.InitialValue = '';
% Signal crt_PT_0d7_Bit7
crt_PT_0d7_Bit7 = Simulink.Signal;
crt_PT_0d7_Bit7.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_0d7_Bit7.RTWInfo.Alias = '';
crt_PT_0d7_Bit7.Description = ...
  ['Frame: RT_SB_INS_Vel_Body_Axes, 215 (0x0d7).' char(10) ...
   'Signal: Bit7.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_0d7_Bit7.DataType = 'boolean';
crt_PT_0d7_Bit7.Min = 0.0;
crt_PT_0d7_Bit7.Max = 1.0;
crt_PT_0d7_Bit7.DocUnits = '';
crt_PT_0d7_Bit7.Dimensions = 1;
crt_PT_0d7_Bit7.Complexity = 'real';
crt_PT_0d7_Bit7.SampleTime = -1;
crt_PT_0d7_Bit7.SamplingMode = 'Sample based';
crt_PT_0d7_Bit7.InitialValue = '';
% Signal crt_PT_0d7_Byte2_Bit0
crt_PT_0d7_Byte2_Bit0 = Simulink.Signal;
crt_PT_0d7_Byte2_Bit0.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_0d7_Byte2_Bit0.RTWInfo.Alias = '';
crt_PT_0d7_Byte2_Bit0.Description = ...
  ['Frame: RT_SB_INS_Vel_Body_Axes, 215 (0x0d7).' char(10) ...
   'Signal: Byte2_Bit0.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_0d7_Byte2_Bit0.DataType = 'boolean';
crt_PT_0d7_Byte2_Bit0.Min = 0.0;
crt_PT_0d7_Byte2_Bit0.Max = 1.0;
crt_PT_0d7_Byte2_Bit0.DocUnits = '';
crt_PT_0d7_Byte2_Bit0.Dimensions = 1;
crt_PT_0d7_Byte2_Bit0.Complexity = 'real';
crt_PT_0d7_Byte2_Bit0.SampleTime = -1;
crt_PT_0d7_Byte2_Bit0.SamplingMode = 'Sample based';
crt_PT_0d7_Byte2_Bit0.InitialValue = '';
% Signal crt_PT_0d7_INS_Vel_Sideways_2D
crt_PT_0d7_INS_Vel_Sideways_2D = Simulink.Signal;
crt_PT_0d7_INS_Vel_Sideways_2D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_0d7_INS_Vel_Sideways_2D.RTWInfo.Alias = '';
crt_PT_0d7_INS_Vel_Sideways_2D.Description = ...
  ['Frame: RT_SB_INS_Vel_Body_Axes, 215 (0x0d7).' char(10) ...
   'Signal: INS_Vel_Sideways_2D.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_0d7_INS_Vel_Sideways_2D.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_0d7_INS_Vel_Sideways_2D.Min = -838.0;
crt_PT_0d7_INS_Vel_Sideways_2D.Max = 838.0;
crt_PT_0d7_INS_Vel_Sideways_2D.DocUnits = 'm/s';
crt_PT_0d7_INS_Vel_Sideways_2D.Dimensions = 1;
crt_PT_0d7_INS_Vel_Sideways_2D.Complexity = 'real';
crt_PT_0d7_INS_Vel_Sideways_2D.SampleTime = -1;
crt_PT_0d7_INS_Vel_Sideways_2D.SamplingMode = 'Sample based';
crt_PT_0d7_INS_Vel_Sideways_2D.InitialValue = '';
% Signal crt_PT_0d7_Byte4_Bits67
crt_PT_0d7_Byte4_Bits67 = Simulink.Signal;
crt_PT_0d7_Byte4_Bits67.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_0d7_Byte4_Bits67.RTWInfo.Alias = '';
crt_PT_0d7_Byte4_Bits67.Description = ...
  ['Frame: RT_SB_INS_Vel_Body_Axes, 215 (0x0d7).' char(10) ...
   'Signal: Byte4_Bits67.' char(10) ...
   'Range (world values): 1.0 ... 3.0 [Mpx selection].' char(10) ...
   'Scaling: WorldValue = BinaryValue [Mpx selection]' ...
  ];
crt_PT_0d7_Byte4_Bits67.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_0d7_Byte4_Bits67.Min = 1.0;
crt_PT_0d7_Byte4_Bits67.Max = 3.0;
crt_PT_0d7_Byte4_Bits67.DocUnits = 'Mpx selection';
crt_PT_0d7_Byte4_Bits67.Dimensions = 1;
crt_PT_0d7_Byte4_Bits67.Complexity = 'real';
crt_PT_0d7_Byte4_Bits67.SampleTime = -1;
crt_PT_0d7_Byte4_Bits67.SamplingMode = 'Sample based';
crt_PT_0d7_Byte4_Bits67.InitialValue = '';
% Signal crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1
crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1 = Simulink.Signal;
crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1.RTWInfo.Alias = '';
crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1.Description = ...
  ['Frame: RT_SB_INS_Vel_Body_Axes, 215 (0x0d7).' char(10) ...
   'Signal: Accuracy_INS_Vel_Body_org.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1.Min = 0.0;
crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1.Max = 255.0;
crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1.DocUnits = '';
crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1.Dimensions = 1;
crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1.Complexity = 'real';
crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1.SampleTime = -1;
crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1.SamplingMode = 'Sample based';
crt_PT_0d7_Accuracy_INS_Vel_Body_org_m1.InitialValue = '';
% Signal crt_PT_0d7_INS_Vel_Forwards_2D_org_m1
crt_PT_0d7_INS_Vel_Forwards_2D_org_m1 = Simulink.Signal;
crt_PT_0d7_INS_Vel_Forwards_2D_org_m1.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_0d7_INS_Vel_Forwards_2D_org_m1.RTWInfo.Alias = '';
crt_PT_0d7_INS_Vel_Forwards_2D_org_m1.Description = ...
  ['Frame: RT_SB_INS_Vel_Body_Axes, 215 (0x0d7).' char(10) ...
   'Signal: INS_Vel_Forwards_2D_org.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_0d7_INS_Vel_Forwards_2D_org_m1.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_0d7_INS_Vel_Forwards_2D_org_m1.Min = -838.0;
crt_PT_0d7_INS_Vel_Forwards_2D_org_m1.Max = 838.0;
crt_PT_0d7_INS_Vel_Forwards_2D_org_m1.DocUnits = 'm/s';
crt_PT_0d7_INS_Vel_Forwards_2D_org_m1.Dimensions = 1;
crt_PT_0d7_INS_Vel_Forwards_2D_org_m1.Complexity = 'real';
crt_PT_0d7_INS_Vel_Forwards_2D_org_m1.SampleTime = -1;
crt_PT_0d7_INS_Vel_Forwards_2D_org_m1.SamplingMode = 'Sample based';
crt_PT_0d7_INS_Vel_Forwards_2D_org_m1.InitialValue = '';
% Signal crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2
crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2 = Simulink.Signal;
crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2.RTWInfo.Alias = '';
crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2.Description = ...
  ['Frame: RT_SB_INS_Vel_Body_Axes, 215 (0x0d7).' char(10) ...
   'Signal: Accuracy_INS_Vel_Body_no2.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2.Min = 0.0;
crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2.Max = 255.0;
crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2.DocUnits = '';
crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2.Dimensions = 1;
crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2.Complexity = 'real';
crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2.SampleTime = -1;
crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2.SamplingMode = 'Sample based';
crt_PT_0d7_Accuracy_INS_Vel_Body_no2_m2.InitialValue = '';
% Signal crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2
crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2 = Simulink.Signal;
crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2.RTWInfo.Alias = '';
crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2.Description = ...
  ['Frame: RT_SB_INS_Vel_Body_Axes, 215 (0x0d7).' char(10) ...
   'Signal: INS_Vel_Forwards_2D_no2.' char(10) ...
   'Range (world values): -104.0 ... 104.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2.Min = -104.0;
crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2.Max = 104.0;
crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2.DocUnits = 'm/s';
crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2.Dimensions = 1;
crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2.Complexity = 'real';
crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2.SampleTime = -1;
crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2.SamplingMode = 'Sample based';
crt_PT_0d7_INS_Vel_Forwards_2D_no2_m2.InitialValue = '';
% Signal crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3
crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3 = Simulink.Signal;
crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3.RTWInfo.Alias = '';
crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3.Description = ...
  ['Frame: RT_SB_INS_Vel_Body_Axes, 215 (0x0d7).' char(10) ...
   'Signal: Accuracy_INS_Vel_Body_no3.' char(10) ...
   'Range (world values): 0.0 ... 32.768 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3.Min = 0.0;
crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3.Max = 32.768;
crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3.DocUnits = '';
crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3.Dimensions = 1;
crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3.Complexity = 'real';
crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3.SampleTime = -1;
crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3.SamplingMode = 'Sample based';
crt_PT_0d7_Accuracy_INS_Vel_Body_no3_m3.InitialValue = '';
% Signal crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3
crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3 = Simulink.Signal;
crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3.RTWInfo.Alias = '';
crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3.Description = ...
  ['Frame: RT_SB_INS_Vel_Body_Axes, 215 (0x0d7).' char(10) ...
   'Signal: INS_Vel_Forwards_2D_no3.' char(10) ...
   'Range (world values): -81.92 ... 81.91 [m/s].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3.Min = -81.92;
crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3.Max = 81.91;
crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3.DocUnits = 'm/s';
crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3.Dimensions = 1;
crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3.Complexity = 'real';
crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3.SampleTime = -1;
crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3.SamplingMode = 'Sample based';
crt_PT_0d7_INS_Vel_Forwards_2D_no3_m3.InitialValue = '';

% Frame RT_DL1MK3_Speed, 8392740 (0x801024)
% Signal crt_PT_801024_Validity_Speed
crt_PT_801024_Validity_Speed = Simulink.Signal;
crt_PT_801024_Validity_Speed.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_801024_Validity_Speed.RTWInfo.Alias = '';
crt_PT_801024_Validity_Speed.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_DL1MK3_Speed, 8392740 (0x801024).' char(10) ...
   'Signal: Validity_Speed.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_801024_Validity_Speed.DataType = 'boolean';
crt_PT_801024_Validity_Speed.Min = 0.0;
crt_PT_801024_Validity_Speed.Max = 1.0;
crt_PT_801024_Validity_Speed.DocUnits = '';
crt_PT_801024_Validity_Speed.Dimensions = 1;
crt_PT_801024_Validity_Speed.Complexity = 'real';
crt_PT_801024_Validity_Speed.SampleTime = -1;
crt_PT_801024_Validity_Speed.SamplingMode = 'Sample based';
crt_PT_801024_Validity_Speed.InitialValue = '';
% Signal crt_PT_801024_Accuracy_Speed
crt_PT_801024_Accuracy_Speed = Simulink.Signal;
crt_PT_801024_Accuracy_Speed.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_801024_Accuracy_Speed.RTWInfo.Alias = '';
crt_PT_801024_Accuracy_Speed.Description = ...
  ['Dimensionless. Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_DL1MK3_Speed, 8392740 (0x801024).' char(10) ...
   'Signal: Accuracy_Speed.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_801024_Accuracy_Speed.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_801024_Accuracy_Speed.Min = 0.0;
crt_PT_801024_Accuracy_Speed.Max = 255.0;
crt_PT_801024_Accuracy_Speed.DocUnits = '';
crt_PT_801024_Accuracy_Speed.Dimensions = 1;
crt_PT_801024_Accuracy_Speed.Complexity = 'real';
crt_PT_801024_Accuracy_Speed.SampleTime = -1;
crt_PT_801024_Accuracy_Speed.SamplingMode = 'Sample based';
crt_PT_801024_Accuracy_Speed.InitialValue = '';
% Signal crt_PT_801024_Direction
crt_PT_801024_Direction = Simulink.Signal;
crt_PT_801024_Direction.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_801024_Direction.RTWInfo.Alias = '';
crt_PT_801024_Direction.Description = ...
  ['Dimensionless. Direction of speed. 1 means forward, -1 means reverse' char(10) ...
   'Frame: RT_DL1MK3_Speed, 8392740 (0x801024).' char(10) ...
   'Signal: Direction.' char(10) ...
   'Range (world values): -1.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = 2.0*BinaryValue + -1.0 []' ...
  ];
crt_PT_801024_Direction.DataType = 'fixdt(0, 8,  2.0, -1.0)';
crt_PT_801024_Direction.Min = -1.0;
crt_PT_801024_Direction.Max = 1.0;
crt_PT_801024_Direction.DocUnits = '';
crt_PT_801024_Direction.Dimensions = 1;
crt_PT_801024_Direction.Complexity = 'real';
crt_PT_801024_Direction.SampleTime = -1;
crt_PT_801024_Direction.SamplingMode = 'Sample based';
crt_PT_801024_Direction.InitialValue = '';
% Signal crt_PT_801024_Speed
crt_PT_801024_Speed = Simulink.Signal;
crt_PT_801024_Speed.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_801024_Speed.RTWInfo.Alias = '';
crt_PT_801024_Speed.Description = ...
  ['Frame: RT_DL1MK3_Speed, 8392740 (0x801024).' char(10) ...
   'Signal: Speed.' char(10) ...
   'Range (world values): -20000.0 ... 20000.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-5*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_801024_Speed.DataType = 'fixdt(1, 32, 1.0E-5, 0.0)';
crt_PT_801024_Speed.Min = -20000.0;
crt_PT_801024_Speed.Max = 20000.0;
crt_PT_801024_Speed.DocUnits = 'm/s';
crt_PT_801024_Speed.Dimensions = 1;
crt_PT_801024_Speed.Complexity = 'real';
crt_PT_801024_Speed.SampleTime = -1;
crt_PT_801024_Speed.SamplingMode = 'Sample based';
crt_PT_801024_Speed.InitialValue = '';

% Frame RT_DL1MK3_GPS_Time, 9175332 (0x8c0124)
% Signal crt_PT_8c0124_Validity_GPS_Time
crt_PT_8c0124_Validity_GPS_Time = Simulink.Signal;
crt_PT_8c0124_Validity_GPS_Time.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0124_Validity_GPS_Time.RTWInfo.Alias = '';
crt_PT_8c0124_Validity_GPS_Time.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_DL1MK3_GPS_Time, 9175332 (0x8c0124).' char(10) ...
   'Signal: Validity_GPS_Time.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0124_Validity_GPS_Time.DataType = 'boolean';
crt_PT_8c0124_Validity_GPS_Time.Min = 0.0;
crt_PT_8c0124_Validity_GPS_Time.Max = 1.0;
crt_PT_8c0124_Validity_GPS_Time.DocUnits = '';
crt_PT_8c0124_Validity_GPS_Time.Dimensions = 1;
crt_PT_8c0124_Validity_GPS_Time.Complexity = 'real';
crt_PT_8c0124_Validity_GPS_Time.SampleTime = -1;
crt_PT_8c0124_Validity_GPS_Time.SamplingMode = 'Sample based';
crt_PT_8c0124_Validity_GPS_Time.InitialValue = '';
% Signal crt_PT_8c0124_Validity_GPS_Week
crt_PT_8c0124_Validity_GPS_Week = Simulink.Signal;
crt_PT_8c0124_Validity_GPS_Week.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0124_Validity_GPS_Week.RTWInfo.Alias = '';
crt_PT_8c0124_Validity_GPS_Week.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_DL1MK3_GPS_Time, 9175332 (0x8c0124).' char(10) ...
   'Signal: Validity_GPS_Week.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0124_Validity_GPS_Week.DataType = 'boolean';
crt_PT_8c0124_Validity_GPS_Week.Min = 0.0;
crt_PT_8c0124_Validity_GPS_Week.Max = 1.0;
crt_PT_8c0124_Validity_GPS_Week.DocUnits = '';
crt_PT_8c0124_Validity_GPS_Week.Dimensions = 1;
crt_PT_8c0124_Validity_GPS_Week.Complexity = 'real';
crt_PT_8c0124_Validity_GPS_Week.SampleTime = -1;
crt_PT_8c0124_Validity_GPS_Week.SamplingMode = 'Sample based';
crt_PT_8c0124_Validity_GPS_Week.InitialValue = '';
% Signal crt_PT_8c0124_Accuracy_GPS_Time
crt_PT_8c0124_Accuracy_GPS_Time = Simulink.Signal;
crt_PT_8c0124_Accuracy_GPS_Time.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0124_Accuracy_GPS_Time.RTWInfo.Alias = '';
crt_PT_8c0124_Accuracy_GPS_Time.Description = ...
  ['Frame: RT_DL1MK3_GPS_Time, 9175332 (0x8c0124).' char(10) ...
   'Signal: Accuracy_GPS_Time.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0124_Accuracy_GPS_Time.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0124_Accuracy_GPS_Time.Min = 0.0;
crt_PT_8c0124_Accuracy_GPS_Time.Max = 255.0;
crt_PT_8c0124_Accuracy_GPS_Time.DocUnits = '';
crt_PT_8c0124_Accuracy_GPS_Time.Dimensions = 1;
crt_PT_8c0124_Accuracy_GPS_Time.Complexity = 'real';
crt_PT_8c0124_Accuracy_GPS_Time.SampleTime = -1;
crt_PT_8c0124_Accuracy_GPS_Time.SamplingMode = 'Sample based';
crt_PT_8c0124_Accuracy_GPS_Time.InitialValue = '';
% Signal crt_PT_8c0124_GPS_Time
crt_PT_8c0124_GPS_Time = Simulink.Signal;
crt_PT_8c0124_GPS_Time.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0124_GPS_Time.RTWInfo.Alias = '';
crt_PT_8c0124_GPS_Time.Description = ...
  ['GPS time is the time in seconds since midnight GMT on Saturday night.' char(10) ...
   'Frame: RT_DL1MK3_GPS_Time, 9175332 (0x8c0124).' char(10) ...
   'Signal: GPS_Time.' char(10) ...
   'Range (world values): 0.0 ... 604800.0 [s].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [s]' ...
  ];
crt_PT_8c0124_GPS_Time.DataType = 'fixdt(0, 32, 0.001, 0.0)';
crt_PT_8c0124_GPS_Time.Min = 0.0;
crt_PT_8c0124_GPS_Time.Max = 604800.0;
crt_PT_8c0124_GPS_Time.DocUnits = 's';
crt_PT_8c0124_GPS_Time.Dimensions = 1;
crt_PT_8c0124_GPS_Time.Complexity = 'real';
crt_PT_8c0124_GPS_Time.SampleTime = -1;
crt_PT_8c0124_GPS_Time.SamplingMode = 'Sample based';
crt_PT_8c0124_GPS_Time.InitialValue = '';
% Signal crt_PT_8c0124_GPS_Week
crt_PT_8c0124_GPS_Week = Simulink.Signal;
crt_PT_8c0124_GPS_Week.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0124_GPS_Week.RTWInfo.Alias = '';
crt_PT_8c0124_GPS_Week.Description = ...
  ['Frame: RT_DL1MK3_GPS_Time, 9175332 (0x8c0124).' char(10) ...
   'Signal: GPS_Week.' char(10) ...
   'Range (world values): 0.0 ... 65535.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0124_GPS_Week.DataType = 'fixdt(0, 16, 1.0, 0.0)';
crt_PT_8c0124_GPS_Week.Min = 0.0;
crt_PT_8c0124_GPS_Week.Max = 65535.0;
crt_PT_8c0124_GPS_Week.DocUnits = '';
crt_PT_8c0124_GPS_Week.Dimensions = 1;
crt_PT_8c0124_GPS_Week.Complexity = 'real';
crt_PT_8c0124_GPS_Week.SampleTime = -1;
crt_PT_8c0124_GPS_Week.SamplingMode = 'Sample based';
crt_PT_8c0124_GPS_Week.InitialValue = '';

% Frame RT_DL1MK3_GPS_Pos_LLH_2, 9175844 (0x8c0324)
% Signal crt_PT_8c0324_GPS_Pos_LLH_Longitude
crt_PT_8c0324_GPS_Pos_LLH_Longitude = Simulink.Signal;
crt_PT_8c0324_GPS_Pos_LLH_Longitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0324_GPS_Pos_LLH_Longitude.RTWInfo.Alias = '';
crt_PT_8c0324_GPS_Pos_LLH_Longitude.Description = ...
  ['Frame: RT_DL1MK3_GPS_Pos_LLH_2, 9175844 (0x8c0324).' char(10) ...
   'Signal: GPS_Pos_LLH_Longitude.' char(10) ...
   'Range (world values): -180.0 ... 180.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 1.0E-7*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8c0324_GPS_Pos_LLH_Longitude.DataType = 'fixdt(1, 32, 1.0E-7, 0.0)';
crt_PT_8c0324_GPS_Pos_LLH_Longitude.Min = -180.0;
crt_PT_8c0324_GPS_Pos_LLH_Longitude.Max = 180.0;
crt_PT_8c0324_GPS_Pos_LLH_Longitude.DocUnits = 'degrees';
crt_PT_8c0324_GPS_Pos_LLH_Longitude.Dimensions = 1;
crt_PT_8c0324_GPS_Pos_LLH_Longitude.Complexity = 'real';
crt_PT_8c0324_GPS_Pos_LLH_Longitude.SampleTime = -1;
crt_PT_8c0324_GPS_Pos_LLH_Longitude.SamplingMode = 'Sample based';
crt_PT_8c0324_GPS_Pos_LLH_Longitude.InitialValue = '';
% Signal crt_PT_8c0324_GPS_Pos_LLH_Altitude
crt_PT_8c0324_GPS_Pos_LLH_Altitude = Simulink.Signal;
crt_PT_8c0324_GPS_Pos_LLH_Altitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0324_GPS_Pos_LLH_Altitude.RTWInfo.Alias = '';
crt_PT_8c0324_GPS_Pos_LLH_Altitude.Description = ...
  ['Frame: RT_DL1MK3_GPS_Pos_LLH_2, 9175844 (0x8c0324).' char(10) ...
   'Signal: GPS_Pos_LLH_Altitude.' char(10) ...
   'Range (world values): -1000.0 ... 100000.0 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8c0324_GPS_Pos_LLH_Altitude.DataType = 'fixdt(1, 32, 0.001, 0.0)';
crt_PT_8c0324_GPS_Pos_LLH_Altitude.Min = -1000.0;
crt_PT_8c0324_GPS_Pos_LLH_Altitude.Max = 100000.0;
crt_PT_8c0324_GPS_Pos_LLH_Altitude.DocUnits = 'm';
crt_PT_8c0324_GPS_Pos_LLH_Altitude.Dimensions = 1;
crt_PT_8c0324_GPS_Pos_LLH_Altitude.Complexity = 'real';
crt_PT_8c0324_GPS_Pos_LLH_Altitude.SampleTime = -1;
crt_PT_8c0324_GPS_Pos_LLH_Altitude.SamplingMode = 'Sample based';
crt_PT_8c0324_GPS_Pos_LLH_Altitude.InitialValue = '';

% Frame RT_DL1MK3_GPS_Pos_LLH_1, 9175588 (0x8c0224)
% Signal crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude
crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude = Simulink.Signal;
crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude.RTWInfo.Alias = '';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_DL1MK3_GPS_Pos_LLH_1, 9175588 (0x8c0224).' char(10) ...
   'Signal: Validity_GPS_Pos_LLH_Latitude.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude.DataType = 'boolean';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude.Min = 0.0;
crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude.Max = 1.0;
crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude.DocUnits = '';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude.Dimensions = 1;
crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude.Complexity = 'real';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude.SampleTime = -1;
crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude.SamplingMode = 'Sample based';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Latitude.InitialValue = '';
% Signal crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude
crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude = Simulink.Signal;
crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude.RTWInfo.Alias = '';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_DL1MK3_GPS_Pos_LLH_1, 9175588 (0x8c0224).' char(10) ...
   'Signal: Validity_GPS_Pos_LLH_Longitude.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude.DataType = 'boolean';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude.Min = 0.0;
crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude.Max = 1.0;
crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude.DocUnits = '';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude.Dimensions = 1;
crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude.Complexity = 'real';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude.SampleTime = -1;
crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude.SamplingMode = 'Sample based';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Longitude.InitialValue = '';
% Signal crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude
crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude = Simulink.Signal;
crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude.RTWInfo.Alias = '';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_DL1MK3_GPS_Pos_LLH_1, 9175588 (0x8c0224).' char(10) ...
   'Signal: Validity_GPS_Pos_LLH_Altitude.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude.DataType = 'boolean';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude.Min = 0.0;
crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude.Max = 1.0;
crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude.DocUnits = '';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude.Dimensions = 1;
crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude.Complexity = 'real';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude.SampleTime = -1;
crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude.SamplingMode = 'Sample based';
crt_PT_8c0224_Validity_GPS_Pos_LLH_Altitude.InitialValue = '';
% Signal crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude = Simulink.Signal;
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude.RTWInfo.Alias = '';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude.Description = ...
  ['This accuracy value applies to both 2D and 3D GPS speed.' char(10) ...
   'Frame: RT_DL1MK3_GPS_Pos_LLH_1, 9175588 (0x8c0224).' char(10) ...
   'Signal: Accuracy_GPS_Pos_LLH_Latitude.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude.Min = 0.0;
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude.Max = 255.0;
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude.DocUnits = '';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude.Dimensions = 1;
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude.Complexity = 'real';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude.SampleTime = -1;
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude.SamplingMode = 'Sample based';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Latitude.InitialValue = '';
% Signal crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude = Simulink.Signal;
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude.RTWInfo.Alias = '';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude.Description = ...
  ['This accuracy value applies to both 2D and 3D GPS speed.' char(10) ...
   'Frame: RT_DL1MK3_GPS_Pos_LLH_1, 9175588 (0x8c0224).' char(10) ...
   'Signal: Accuracy_GPS_Pos_LLH_Longitude.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude.Min = 0.0;
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude.Max = 255.0;
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude.DocUnits = '';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude.Dimensions = 1;
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude.Complexity = 'real';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude.SampleTime = -1;
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude.SamplingMode = 'Sample based';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Longitude.InitialValue = '';
% Signal crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude = Simulink.Signal;
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude.RTWInfo.Alias = '';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude.Description = ...
  ['This accuracy value applies to both 2D and 3D GPS speed.' char(10) ...
   'Frame: RT_DL1MK3_GPS_Pos_LLH_1, 9175588 (0x8c0224).' char(10) ...
   'Signal: Accuracy_GPS_Pos_LLH_Altitude.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude.Min = 0.0;
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude.Max = 255.0;
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude.DocUnits = '';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude.Dimensions = 1;
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude.Complexity = 'real';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude.SampleTime = -1;
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude.SamplingMode = 'Sample based';
crt_PT_8c0224_Accuracy_GPS_Pos_LLH_Altitude.InitialValue = '';
% Signal crt_PT_8c0224_GPS_Pos_LLH_Latitude
crt_PT_8c0224_GPS_Pos_LLH_Latitude = Simulink.Signal;
crt_PT_8c0224_GPS_Pos_LLH_Latitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0224_GPS_Pos_LLH_Latitude.RTWInfo.Alias = '';
crt_PT_8c0224_GPS_Pos_LLH_Latitude.Description = ...
  ['Frame: RT_DL1MK3_GPS_Pos_LLH_1, 9175588 (0x8c0224).' char(10) ...
   'Signal: GPS_Pos_LLH_Latitude.' char(10) ...
   'Range (world values): -90.0 ... 90.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 1.0E-7*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8c0224_GPS_Pos_LLH_Latitude.DataType = 'fixdt(1, 32, 1.0E-7, 0.0)';
crt_PT_8c0224_GPS_Pos_LLH_Latitude.Min = -90.0;
crt_PT_8c0224_GPS_Pos_LLH_Latitude.Max = 90.0;
crt_PT_8c0224_GPS_Pos_LLH_Latitude.DocUnits = 'degrees';
crt_PT_8c0224_GPS_Pos_LLH_Latitude.Dimensions = 1;
crt_PT_8c0224_GPS_Pos_LLH_Latitude.Complexity = 'real';
crt_PT_8c0224_GPS_Pos_LLH_Latitude.SampleTime = -1;
crt_PT_8c0224_GPS_Pos_LLH_Latitude.SamplingMode = 'Sample based';
crt_PT_8c0224_GPS_Pos_LLH_Latitude.InitialValue = '';

% Frame RT_DL1MK3_GPS_Speed, 1234 (0x4d2)
% Signal crt_PT_4d2_Validity_GPS_Speed_2D
crt_PT_4d2_Validity_GPS_Speed_2D = Simulink.Signal;
crt_PT_4d2_Validity_GPS_Speed_2D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_4d2_Validity_GPS_Speed_2D.RTWInfo.Alias = '';
crt_PT_4d2_Validity_GPS_Speed_2D.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_DL1MK3_GPS_Speed, 1234 (0x4d2).' char(10) ...
   'Signal: Validity_GPS_Speed_2D.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_4d2_Validity_GPS_Speed_2D.DataType = 'boolean';
crt_PT_4d2_Validity_GPS_Speed_2D.Min = 0.0;
crt_PT_4d2_Validity_GPS_Speed_2D.Max = 1.0;
crt_PT_4d2_Validity_GPS_Speed_2D.DocUnits = '';
crt_PT_4d2_Validity_GPS_Speed_2D.Dimensions = 1;
crt_PT_4d2_Validity_GPS_Speed_2D.Complexity = 'real';
crt_PT_4d2_Validity_GPS_Speed_2D.SampleTime = -1;
crt_PT_4d2_Validity_GPS_Speed_2D.SamplingMode = 'Sample based';
crt_PT_4d2_Validity_GPS_Speed_2D.InitialValue = '';
% Signal crt_PT_4d2_Validity_GPS_Speed_3D
crt_PT_4d2_Validity_GPS_Speed_3D = Simulink.Signal;
crt_PT_4d2_Validity_GPS_Speed_3D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_4d2_Validity_GPS_Speed_3D.RTWInfo.Alias = '';
crt_PT_4d2_Validity_GPS_Speed_3D.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_DL1MK3_GPS_Speed, 1234 (0x4d2).' char(10) ...
   'Signal: Validity_GPS_Speed_3D.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_4d2_Validity_GPS_Speed_3D.DataType = 'boolean';
crt_PT_4d2_Validity_GPS_Speed_3D.Min = 0.0;
crt_PT_4d2_Validity_GPS_Speed_3D.Max = 1.0;
crt_PT_4d2_Validity_GPS_Speed_3D.DocUnits = '';
crt_PT_4d2_Validity_GPS_Speed_3D.Dimensions = 1;
crt_PT_4d2_Validity_GPS_Speed_3D.Complexity = 'real';
crt_PT_4d2_Validity_GPS_Speed_3D.SampleTime = -1;
crt_PT_4d2_Validity_GPS_Speed_3D.SamplingMode = 'Sample based';
crt_PT_4d2_Validity_GPS_Speed_3D.InitialValue = '';
% Signal crt_PT_4d2_Accuracy_GPS_Speed
crt_PT_4d2_Accuracy_GPS_Speed = Simulink.Signal;
crt_PT_4d2_Accuracy_GPS_Speed.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_4d2_Accuracy_GPS_Speed.RTWInfo.Alias = '';
crt_PT_4d2_Accuracy_GPS_Speed.Description = ...
  ['This accuracy value applies to both 2D and 3D GPS speed.' char(10) ...
   'Frame: RT_DL1MK3_GPS_Speed, 1234 (0x4d2).' char(10) ...
   'Signal: Accuracy_GPS_Speed.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_4d2_Accuracy_GPS_Speed.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_4d2_Accuracy_GPS_Speed.Min = 0.0;
crt_PT_4d2_Accuracy_GPS_Speed.Max = 255.0;
crt_PT_4d2_Accuracy_GPS_Speed.DocUnits = '';
crt_PT_4d2_Accuracy_GPS_Speed.Dimensions = 1;
crt_PT_4d2_Accuracy_GPS_Speed.Complexity = 'real';
crt_PT_4d2_Accuracy_GPS_Speed.SampleTime = -1;
crt_PT_4d2_Accuracy_GPS_Speed.SamplingMode = 'Sample based';
crt_PT_4d2_Accuracy_GPS_Speed.InitialValue = '';
% Signal crt_PT_4d2_GPS_Speed_2D
crt_PT_4d2_GPS_Speed_2D = Simulink.Signal;
crt_PT_4d2_GPS_Speed_2D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_4d2_GPS_Speed_2D.RTWInfo.Alias = '';
crt_PT_4d2_GPS_Speed_2D.Description = ...
  ['This is GPS scalar 2D speed - scalar speed with no local Z axis component included.' char(10) ...
   'Frame: RT_DL1MK3_GPS_Speed, 1234 (0x4d2).' char(10) ...
   'Signal: GPS_Speed_2D.' char(10) ...
   'Range (world values): 0.0 ... 1675.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_4d2_GPS_Speed_2D.DataType = 'fixdt(0, 32, 1.0E-4, 0.0)';
crt_PT_4d2_GPS_Speed_2D.Min = 0.0;
crt_PT_4d2_GPS_Speed_2D.Max = 1675.0;
crt_PT_4d2_GPS_Speed_2D.DocUnits = 'm/s';
crt_PT_4d2_GPS_Speed_2D.Dimensions = 1;
crt_PT_4d2_GPS_Speed_2D.Complexity = 'real';
crt_PT_4d2_GPS_Speed_2D.SampleTime = -1;
crt_PT_4d2_GPS_Speed_2D.SamplingMode = 'Sample based';
crt_PT_4d2_GPS_Speed_2D.InitialValue = '';
% Signal crt_PT_4d2_GPS_Speed_3D
crt_PT_4d2_GPS_Speed_3D = Simulink.Signal;
crt_PT_4d2_GPS_Speed_3D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_4d2_GPS_Speed_3D.RTWInfo.Alias = '';
crt_PT_4d2_GPS_Speed_3D.Description = ...
  ['This is GPS scalar 3D speed - scalar speed with the local Z axis component included.' char(10) ...
   'Frame: RT_DL1MK3_GPS_Speed, 1234 (0x4d2).' char(10) ...
   'Signal: GPS_Speed_3D.' char(10) ...
   'Range (world values): 0.0 ... 1675.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_4d2_GPS_Speed_3D.DataType = 'fixdt(0, 32, 1.0E-4, 0.0)';
crt_PT_4d2_GPS_Speed_3D.Min = 0.0;
crt_PT_4d2_GPS_Speed_3D.Max = 1675.0;
crt_PT_4d2_GPS_Speed_3D.DocUnits = 'm/s';
crt_PT_4d2_GPS_Speed_3D.Dimensions = 1;
crt_PT_4d2_GPS_Speed_3D.Complexity = 'real';
crt_PT_4d2_GPS_Speed_3D.SampleTime = -1;
crt_PT_4d2_GPS_Speed_3D.SamplingMode = 'Sample based';
crt_PT_4d2_GPS_Speed_3D.InitialValue = '';

% Frame RT_IRTemp_Temp_RR_2, 9963557 (0x980825)
% Signal crt_PT_980825_IR_Temperature_29
crt_PT_980825_IR_Temperature_29 = Simulink.Signal;
crt_PT_980825_IR_Temperature_29.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980825_IR_Temperature_29.RTWInfo.Alias = '';
crt_PT_980825_IR_Temperature_29.Description = ...
  ['Frame: RT_IRTemp_Temp_RR_2, 9963557 (0x980825).' char(10) ...
   'Signal: IR_Temperature_29.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980825_IR_Temperature_29.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980825_IR_Temperature_29.Min = 0.0;
crt_PT_980825_IR_Temperature_29.Max = 0.0;
crt_PT_980825_IR_Temperature_29.DocUnits = '';
crt_PT_980825_IR_Temperature_29.Dimensions = 1;
crt_PT_980825_IR_Temperature_29.Complexity = 'real';
crt_PT_980825_IR_Temperature_29.SampleTime = -1;
crt_PT_980825_IR_Temperature_29.SamplingMode = 'Sample based';
crt_PT_980825_IR_Temperature_29.InitialValue = '';
% Signal crt_PT_980825_IR_Temperature_30
crt_PT_980825_IR_Temperature_30 = Simulink.Signal;
crt_PT_980825_IR_Temperature_30.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980825_IR_Temperature_30.RTWInfo.Alias = '';
crt_PT_980825_IR_Temperature_30.Description = ...
  ['Frame: RT_IRTemp_Temp_RR_2, 9963557 (0x980825).' char(10) ...
   'Signal: IR_Temperature_30.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980825_IR_Temperature_30.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980825_IR_Temperature_30.Min = 0.0;
crt_PT_980825_IR_Temperature_30.Max = 0.0;
crt_PT_980825_IR_Temperature_30.DocUnits = '';
crt_PT_980825_IR_Temperature_30.Dimensions = 1;
crt_PT_980825_IR_Temperature_30.Complexity = 'real';
crt_PT_980825_IR_Temperature_30.SampleTime = -1;
crt_PT_980825_IR_Temperature_30.SamplingMode = 'Sample based';
crt_PT_980825_IR_Temperature_30.InitialValue = '';
% Signal crt_PT_980825_IR_Temperature_31
crt_PT_980825_IR_Temperature_31 = Simulink.Signal;
crt_PT_980825_IR_Temperature_31.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980825_IR_Temperature_31.RTWInfo.Alias = '';
crt_PT_980825_IR_Temperature_31.Description = ...
  ['Frame: RT_IRTemp_Temp_RR_2, 9963557 (0x980825).' char(10) ...
   'Signal: IR_Temperature_31.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980825_IR_Temperature_31.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980825_IR_Temperature_31.Min = 0.0;
crt_PT_980825_IR_Temperature_31.Max = 0.0;
crt_PT_980825_IR_Temperature_31.DocUnits = '';
crt_PT_980825_IR_Temperature_31.Dimensions = 1;
crt_PT_980825_IR_Temperature_31.Complexity = 'real';
crt_PT_980825_IR_Temperature_31.SampleTime = -1;
crt_PT_980825_IR_Temperature_31.SamplingMode = 'Sample based';
crt_PT_980825_IR_Temperature_31.InitialValue = '';
% Signal crt_PT_980825_IR_Temperature_32
crt_PT_980825_IR_Temperature_32 = Simulink.Signal;
crt_PT_980825_IR_Temperature_32.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980825_IR_Temperature_32.RTWInfo.Alias = '';
crt_PT_980825_IR_Temperature_32.Description = ...
  ['Frame: RT_IRTemp_Temp_RR_2, 9963557 (0x980825).' char(10) ...
   'Signal: IR_Temperature_32.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980825_IR_Temperature_32.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980825_IR_Temperature_32.Min = 0.0;
crt_PT_980825_IR_Temperature_32.Max = 0.0;
crt_PT_980825_IR_Temperature_32.DocUnits = '';
crt_PT_980825_IR_Temperature_32.Dimensions = 1;
crt_PT_980825_IR_Temperature_32.Complexity = 'real';
crt_PT_980825_IR_Temperature_32.SampleTime = -1;
crt_PT_980825_IR_Temperature_32.SamplingMode = 'Sample based';
crt_PT_980825_IR_Temperature_32.InitialValue = '';

% Frame RT_IRTemp_Temp_FL_2, 9962021 (0x980225)
% Signal crt_PT_980225_IR_Temperature_5
crt_PT_980225_IR_Temperature_5 = Simulink.Signal;
crt_PT_980225_IR_Temperature_5.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980225_IR_Temperature_5.RTWInfo.Alias = '';
crt_PT_980225_IR_Temperature_5.Description = ...
  ['Frame: RT_IRTemp_Temp_FL_2, 9962021 (0x980225).' char(10) ...
   'Signal: IR_Temperature_5.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980225_IR_Temperature_5.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980225_IR_Temperature_5.Min = 0.0;
crt_PT_980225_IR_Temperature_5.Max = 0.0;
crt_PT_980225_IR_Temperature_5.DocUnits = '';
crt_PT_980225_IR_Temperature_5.Dimensions = 1;
crt_PT_980225_IR_Temperature_5.Complexity = 'real';
crt_PT_980225_IR_Temperature_5.SampleTime = -1;
crt_PT_980225_IR_Temperature_5.SamplingMode = 'Sample based';
crt_PT_980225_IR_Temperature_5.InitialValue = '';
% Signal crt_PT_980225_IR_Temperature_6
crt_PT_980225_IR_Temperature_6 = Simulink.Signal;
crt_PT_980225_IR_Temperature_6.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980225_IR_Temperature_6.RTWInfo.Alias = '';
crt_PT_980225_IR_Temperature_6.Description = ...
  ['Frame: RT_IRTemp_Temp_FL_2, 9962021 (0x980225).' char(10) ...
   'Signal: IR_Temperature_6.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980225_IR_Temperature_6.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980225_IR_Temperature_6.Min = 0.0;
crt_PT_980225_IR_Temperature_6.Max = 0.0;
crt_PT_980225_IR_Temperature_6.DocUnits = '';
crt_PT_980225_IR_Temperature_6.Dimensions = 1;
crt_PT_980225_IR_Temperature_6.Complexity = 'real';
crt_PT_980225_IR_Temperature_6.SampleTime = -1;
crt_PT_980225_IR_Temperature_6.SamplingMode = 'Sample based';
crt_PT_980225_IR_Temperature_6.InitialValue = '';
% Signal crt_PT_980225_IR_Temperature_7
crt_PT_980225_IR_Temperature_7 = Simulink.Signal;
crt_PT_980225_IR_Temperature_7.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980225_IR_Temperature_7.RTWInfo.Alias = '';
crt_PT_980225_IR_Temperature_7.Description = ...
  ['Frame: RT_IRTemp_Temp_FL_2, 9962021 (0x980225).' char(10) ...
   'Signal: IR_Temperature_7.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980225_IR_Temperature_7.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980225_IR_Temperature_7.Min = 0.0;
crt_PT_980225_IR_Temperature_7.Max = 0.0;
crt_PT_980225_IR_Temperature_7.DocUnits = '';
crt_PT_980225_IR_Temperature_7.Dimensions = 1;
crt_PT_980225_IR_Temperature_7.Complexity = 'real';
crt_PT_980225_IR_Temperature_7.SampleTime = -1;
crt_PT_980225_IR_Temperature_7.SamplingMode = 'Sample based';
crt_PT_980225_IR_Temperature_7.InitialValue = '';
% Signal crt_PT_980225_IR_Temperature_8
crt_PT_980225_IR_Temperature_8 = Simulink.Signal;
crt_PT_980225_IR_Temperature_8.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980225_IR_Temperature_8.RTWInfo.Alias = '';
crt_PT_980225_IR_Temperature_8.Description = ...
  ['Frame: RT_IRTemp_Temp_FL_2, 9962021 (0x980225).' char(10) ...
   'Signal: IR_Temperature_8.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980225_IR_Temperature_8.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980225_IR_Temperature_8.Min = 0.0;
crt_PT_980225_IR_Temperature_8.Max = 0.0;
crt_PT_980225_IR_Temperature_8.DocUnits = '';
crt_PT_980225_IR_Temperature_8.Dimensions = 1;
crt_PT_980225_IR_Temperature_8.Complexity = 'real';
crt_PT_980225_IR_Temperature_8.SampleTime = -1;
crt_PT_980225_IR_Temperature_8.SamplingMode = 'Sample based';
crt_PT_980225_IR_Temperature_8.InitialValue = '';

% Frame RT_IRTemp_Temp_RR_1, 9963301 (0x980725)
% Signal crt_PT_980725_IR_Temperature_25
crt_PT_980725_IR_Temperature_25 = Simulink.Signal;
crt_PT_980725_IR_Temperature_25.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980725_IR_Temperature_25.RTWInfo.Alias = '';
crt_PT_980725_IR_Temperature_25.Description = ...
  ['Frame: RT_IRTemp_Temp_RR_1, 9963301 (0x980725).' char(10) ...
   'Signal: IR_Temperature_25.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980725_IR_Temperature_25.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980725_IR_Temperature_25.Min = 0.0;
crt_PT_980725_IR_Temperature_25.Max = 0.0;
crt_PT_980725_IR_Temperature_25.DocUnits = '';
crt_PT_980725_IR_Temperature_25.Dimensions = 1;
crt_PT_980725_IR_Temperature_25.Complexity = 'real';
crt_PT_980725_IR_Temperature_25.SampleTime = -1;
crt_PT_980725_IR_Temperature_25.SamplingMode = 'Sample based';
crt_PT_980725_IR_Temperature_25.InitialValue = '';
% Signal crt_PT_980725_IR_Temperature_26
crt_PT_980725_IR_Temperature_26 = Simulink.Signal;
crt_PT_980725_IR_Temperature_26.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980725_IR_Temperature_26.RTWInfo.Alias = '';
crt_PT_980725_IR_Temperature_26.Description = ...
  ['Frame: RT_IRTemp_Temp_RR_1, 9963301 (0x980725).' char(10) ...
   'Signal: IR_Temperature_26.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980725_IR_Temperature_26.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980725_IR_Temperature_26.Min = 0.0;
crt_PT_980725_IR_Temperature_26.Max = 0.0;
crt_PT_980725_IR_Temperature_26.DocUnits = '';
crt_PT_980725_IR_Temperature_26.Dimensions = 1;
crt_PT_980725_IR_Temperature_26.Complexity = 'real';
crt_PT_980725_IR_Temperature_26.SampleTime = -1;
crt_PT_980725_IR_Temperature_26.SamplingMode = 'Sample based';
crt_PT_980725_IR_Temperature_26.InitialValue = '';
% Signal crt_PT_980725_IR_Temperature_27
crt_PT_980725_IR_Temperature_27 = Simulink.Signal;
crt_PT_980725_IR_Temperature_27.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980725_IR_Temperature_27.RTWInfo.Alias = '';
crt_PT_980725_IR_Temperature_27.Description = ...
  ['Frame: RT_IRTemp_Temp_RR_1, 9963301 (0x980725).' char(10) ...
   'Signal: IR_Temperature_27.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980725_IR_Temperature_27.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980725_IR_Temperature_27.Min = 0.0;
crt_PT_980725_IR_Temperature_27.Max = 0.0;
crt_PT_980725_IR_Temperature_27.DocUnits = '';
crt_PT_980725_IR_Temperature_27.Dimensions = 1;
crt_PT_980725_IR_Temperature_27.Complexity = 'real';
crt_PT_980725_IR_Temperature_27.SampleTime = -1;
crt_PT_980725_IR_Temperature_27.SamplingMode = 'Sample based';
crt_PT_980725_IR_Temperature_27.InitialValue = '';
% Signal crt_PT_980725_IR_Temperature_28
crt_PT_980725_IR_Temperature_28 = Simulink.Signal;
crt_PT_980725_IR_Temperature_28.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980725_IR_Temperature_28.RTWInfo.Alias = '';
crt_PT_980725_IR_Temperature_28.Description = ...
  ['Frame: RT_IRTemp_Temp_RR_1, 9963301 (0x980725).' char(10) ...
   'Signal: IR_Temperature_28.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980725_IR_Temperature_28.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980725_IR_Temperature_28.Min = 0.0;
crt_PT_980725_IR_Temperature_28.Max = 0.0;
crt_PT_980725_IR_Temperature_28.DocUnits = '';
crt_PT_980725_IR_Temperature_28.Dimensions = 1;
crt_PT_980725_IR_Temperature_28.Complexity = 'real';
crt_PT_980725_IR_Temperature_28.SampleTime = -1;
crt_PT_980725_IR_Temperature_28.SamplingMode = 'Sample based';
crt_PT_980725_IR_Temperature_28.InitialValue = '';

% Frame RT_IRTemp_Temp_RL_1, 9962789 (0x980525)
% Signal crt_PT_980525_IR_Temperature_17
crt_PT_980525_IR_Temperature_17 = Simulink.Signal;
crt_PT_980525_IR_Temperature_17.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980525_IR_Temperature_17.RTWInfo.Alias = '';
crt_PT_980525_IR_Temperature_17.Description = ...
  ['Frame: RT_IRTemp_Temp_RL_1, 9962789 (0x980525).' char(10) ...
   'Signal: IR_Temperature_17.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980525_IR_Temperature_17.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980525_IR_Temperature_17.Min = 0.0;
crt_PT_980525_IR_Temperature_17.Max = 0.0;
crt_PT_980525_IR_Temperature_17.DocUnits = '';
crt_PT_980525_IR_Temperature_17.Dimensions = 1;
crt_PT_980525_IR_Temperature_17.Complexity = 'real';
crt_PT_980525_IR_Temperature_17.SampleTime = -1;
crt_PT_980525_IR_Temperature_17.SamplingMode = 'Sample based';
crt_PT_980525_IR_Temperature_17.InitialValue = '';
% Signal crt_PT_980525_IR_Temperature_18
crt_PT_980525_IR_Temperature_18 = Simulink.Signal;
crt_PT_980525_IR_Temperature_18.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980525_IR_Temperature_18.RTWInfo.Alias = '';
crt_PT_980525_IR_Temperature_18.Description = ...
  ['Frame: RT_IRTemp_Temp_RL_1, 9962789 (0x980525).' char(10) ...
   'Signal: IR_Temperature_18.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980525_IR_Temperature_18.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980525_IR_Temperature_18.Min = 0.0;
crt_PT_980525_IR_Temperature_18.Max = 0.0;
crt_PT_980525_IR_Temperature_18.DocUnits = '';
crt_PT_980525_IR_Temperature_18.Dimensions = 1;
crt_PT_980525_IR_Temperature_18.Complexity = 'real';
crt_PT_980525_IR_Temperature_18.SampleTime = -1;
crt_PT_980525_IR_Temperature_18.SamplingMode = 'Sample based';
crt_PT_980525_IR_Temperature_18.InitialValue = '';
% Signal crt_PT_980525_IR_Temperature_19
crt_PT_980525_IR_Temperature_19 = Simulink.Signal;
crt_PT_980525_IR_Temperature_19.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980525_IR_Temperature_19.RTWInfo.Alias = '';
crt_PT_980525_IR_Temperature_19.Description = ...
  ['Frame: RT_IRTemp_Temp_RL_1, 9962789 (0x980525).' char(10) ...
   'Signal: IR_Temperature_19.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980525_IR_Temperature_19.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980525_IR_Temperature_19.Min = 0.0;
crt_PT_980525_IR_Temperature_19.Max = 0.0;
crt_PT_980525_IR_Temperature_19.DocUnits = '';
crt_PT_980525_IR_Temperature_19.Dimensions = 1;
crt_PT_980525_IR_Temperature_19.Complexity = 'real';
crt_PT_980525_IR_Temperature_19.SampleTime = -1;
crt_PT_980525_IR_Temperature_19.SamplingMode = 'Sample based';
crt_PT_980525_IR_Temperature_19.InitialValue = '';
% Signal crt_PT_980525_IR_Temperature_20
crt_PT_980525_IR_Temperature_20 = Simulink.Signal;
crt_PT_980525_IR_Temperature_20.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980525_IR_Temperature_20.RTWInfo.Alias = '';
crt_PT_980525_IR_Temperature_20.Description = ...
  ['Frame: RT_IRTemp_Temp_RL_1, 9962789 (0x980525).' char(10) ...
   'Signal: IR_Temperature_20.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980525_IR_Temperature_20.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980525_IR_Temperature_20.Min = 0.0;
crt_PT_980525_IR_Temperature_20.Max = 0.0;
crt_PT_980525_IR_Temperature_20.DocUnits = '';
crt_PT_980525_IR_Temperature_20.Dimensions = 1;
crt_PT_980525_IR_Temperature_20.Complexity = 'real';
crt_PT_980525_IR_Temperature_20.SampleTime = -1;
crt_PT_980525_IR_Temperature_20.SamplingMode = 'Sample based';
crt_PT_980525_IR_Temperature_20.InitialValue = '';

% Frame RT_IRTemp_Temp_FR_1, 9962277 (0x980325)
% Signal crt_PT_980325_IR_Temperature_9
crt_PT_980325_IR_Temperature_9 = Simulink.Signal;
crt_PT_980325_IR_Temperature_9.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980325_IR_Temperature_9.RTWInfo.Alias = '';
crt_PT_980325_IR_Temperature_9.Description = ...
  ['Frame: RT_IRTemp_Temp_FR_1, 9962277 (0x980325).' char(10) ...
   'Signal: IR_Temperature_9.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980325_IR_Temperature_9.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980325_IR_Temperature_9.Min = 0.0;
crt_PT_980325_IR_Temperature_9.Max = 0.0;
crt_PT_980325_IR_Temperature_9.DocUnits = '';
crt_PT_980325_IR_Temperature_9.Dimensions = 1;
crt_PT_980325_IR_Temperature_9.Complexity = 'real';
crt_PT_980325_IR_Temperature_9.SampleTime = -1;
crt_PT_980325_IR_Temperature_9.SamplingMode = 'Sample based';
crt_PT_980325_IR_Temperature_9.InitialValue = '';
% Signal crt_PT_980325_IR_Temperature_10
crt_PT_980325_IR_Temperature_10 = Simulink.Signal;
crt_PT_980325_IR_Temperature_10.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980325_IR_Temperature_10.RTWInfo.Alias = '';
crt_PT_980325_IR_Temperature_10.Description = ...
  ['Frame: RT_IRTemp_Temp_FR_1, 9962277 (0x980325).' char(10) ...
   'Signal: IR_Temperature_10.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980325_IR_Temperature_10.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980325_IR_Temperature_10.Min = 0.0;
crt_PT_980325_IR_Temperature_10.Max = 0.0;
crt_PT_980325_IR_Temperature_10.DocUnits = '';
crt_PT_980325_IR_Temperature_10.Dimensions = 1;
crt_PT_980325_IR_Temperature_10.Complexity = 'real';
crt_PT_980325_IR_Temperature_10.SampleTime = -1;
crt_PT_980325_IR_Temperature_10.SamplingMode = 'Sample based';
crt_PT_980325_IR_Temperature_10.InitialValue = '';
% Signal crt_PT_980325_IR_Temperature_11
crt_PT_980325_IR_Temperature_11 = Simulink.Signal;
crt_PT_980325_IR_Temperature_11.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980325_IR_Temperature_11.RTWInfo.Alias = '';
crt_PT_980325_IR_Temperature_11.Description = ...
  ['Frame: RT_IRTemp_Temp_FR_1, 9962277 (0x980325).' char(10) ...
   'Signal: IR_Temperature_11.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980325_IR_Temperature_11.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980325_IR_Temperature_11.Min = 0.0;
crt_PT_980325_IR_Temperature_11.Max = 0.0;
crt_PT_980325_IR_Temperature_11.DocUnits = '';
crt_PT_980325_IR_Temperature_11.Dimensions = 1;
crt_PT_980325_IR_Temperature_11.Complexity = 'real';
crt_PT_980325_IR_Temperature_11.SampleTime = -1;
crt_PT_980325_IR_Temperature_11.SamplingMode = 'Sample based';
crt_PT_980325_IR_Temperature_11.InitialValue = '';
% Signal crt_PT_980325_IR_Temperature_12
crt_PT_980325_IR_Temperature_12 = Simulink.Signal;
crt_PT_980325_IR_Temperature_12.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980325_IR_Temperature_12.RTWInfo.Alias = '';
crt_PT_980325_IR_Temperature_12.Description = ...
  ['Frame: RT_IRTemp_Temp_FR_1, 9962277 (0x980325).' char(10) ...
   'Signal: IR_Temperature_12.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980325_IR_Temperature_12.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980325_IR_Temperature_12.Min = 0.0;
crt_PT_980325_IR_Temperature_12.Max = 0.0;
crt_PT_980325_IR_Temperature_12.DocUnits = '';
crt_PT_980325_IR_Temperature_12.Dimensions = 1;
crt_PT_980325_IR_Temperature_12.Complexity = 'real';
crt_PT_980325_IR_Temperature_12.SampleTime = -1;
crt_PT_980325_IR_Temperature_12.SamplingMode = 'Sample based';
crt_PT_980325_IR_Temperature_12.InitialValue = '';

% Frame RT_IRTemp_Temp_FL_1, 9961765 (0x980125)
% Signal crt_PT_980125_IR_Temperature_1
crt_PT_980125_IR_Temperature_1 = Simulink.Signal;
crt_PT_980125_IR_Temperature_1.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980125_IR_Temperature_1.RTWInfo.Alias = '';
crt_PT_980125_IR_Temperature_1.Description = ...
  ['Frame: RT_IRTemp_Temp_FL_1, 9961765 (0x980125).' char(10) ...
   'Signal: IR_Temperature_1.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980125_IR_Temperature_1.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980125_IR_Temperature_1.Min = 0.0;
crt_PT_980125_IR_Temperature_1.Max = 0.0;
crt_PT_980125_IR_Temperature_1.DocUnits = '';
crt_PT_980125_IR_Temperature_1.Dimensions = 1;
crt_PT_980125_IR_Temperature_1.Complexity = 'real';
crt_PT_980125_IR_Temperature_1.SampleTime = -1;
crt_PT_980125_IR_Temperature_1.SamplingMode = 'Sample based';
crt_PT_980125_IR_Temperature_1.InitialValue = '';
% Signal crt_PT_980125_IR_Temperature_2
crt_PT_980125_IR_Temperature_2 = Simulink.Signal;
crt_PT_980125_IR_Temperature_2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980125_IR_Temperature_2.RTWInfo.Alias = '';
crt_PT_980125_IR_Temperature_2.Description = ...
  ['Frame: RT_IRTemp_Temp_FL_1, 9961765 (0x980125).' char(10) ...
   'Signal: IR_Temperature_2.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980125_IR_Temperature_2.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980125_IR_Temperature_2.Min = 0.0;
crt_PT_980125_IR_Temperature_2.Max = 0.0;
crt_PT_980125_IR_Temperature_2.DocUnits = '';
crt_PT_980125_IR_Temperature_2.Dimensions = 1;
crt_PT_980125_IR_Temperature_2.Complexity = 'real';
crt_PT_980125_IR_Temperature_2.SampleTime = -1;
crt_PT_980125_IR_Temperature_2.SamplingMode = 'Sample based';
crt_PT_980125_IR_Temperature_2.InitialValue = '';
% Signal crt_PT_980125_IR_Temperature_3
crt_PT_980125_IR_Temperature_3 = Simulink.Signal;
crt_PT_980125_IR_Temperature_3.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980125_IR_Temperature_3.RTWInfo.Alias = '';
crt_PT_980125_IR_Temperature_3.Description = ...
  ['Frame: RT_IRTemp_Temp_FL_1, 9961765 (0x980125).' char(10) ...
   'Signal: IR_Temperature_3.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980125_IR_Temperature_3.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980125_IR_Temperature_3.Min = 0.0;
crt_PT_980125_IR_Temperature_3.Max = 0.0;
crt_PT_980125_IR_Temperature_3.DocUnits = '';
crt_PT_980125_IR_Temperature_3.Dimensions = 1;
crt_PT_980125_IR_Temperature_3.Complexity = 'real';
crt_PT_980125_IR_Temperature_3.SampleTime = -1;
crt_PT_980125_IR_Temperature_3.SamplingMode = 'Sample based';
crt_PT_980125_IR_Temperature_3.InitialValue = '';
% Signal crt_PT_980125_IR_Temperature_4
crt_PT_980125_IR_Temperature_4 = Simulink.Signal;
crt_PT_980125_IR_Temperature_4.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980125_IR_Temperature_4.RTWInfo.Alias = '';
crt_PT_980125_IR_Temperature_4.Description = ...
  ['Frame: RT_IRTemp_Temp_FL_1, 9961765 (0x980125).' char(10) ...
   'Signal: IR_Temperature_4.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980125_IR_Temperature_4.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980125_IR_Temperature_4.Min = 0.0;
crt_PT_980125_IR_Temperature_4.Max = 0.0;
crt_PT_980125_IR_Temperature_4.DocUnits = '';
crt_PT_980125_IR_Temperature_4.Dimensions = 1;
crt_PT_980125_IR_Temperature_4.Complexity = 'real';
crt_PT_980125_IR_Temperature_4.SampleTime = -1;
crt_PT_980125_IR_Temperature_4.SamplingMode = 'Sample based';
crt_PT_980125_IR_Temperature_4.InitialValue = '';

% Frame RT_IRTemp_Temp_32, 9510949 (0x912025)
% Signal crt_PT_912025_IR_Temperature_32
crt_PT_912025_IR_Temperature_32 = Simulink.Signal;
crt_PT_912025_IR_Temperature_32.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_912025_IR_Temperature_32.RTWInfo.Alias = '';
crt_PT_912025_IR_Temperature_32.Description = ...
  ['Frame: RT_IRTemp_Temp_32, 9510949 (0x912025).' char(10) ...
   'Signal: IR_Temperature_32.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_912025_IR_Temperature_32.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_912025_IR_Temperature_32.Min = 0.0;
crt_PT_912025_IR_Temperature_32.Max = 0.0;
crt_PT_912025_IR_Temperature_32.DocUnits = '';
crt_PT_912025_IR_Temperature_32.Dimensions = 1;
crt_PT_912025_IR_Temperature_32.Complexity = 'real';
crt_PT_912025_IR_Temperature_32.SampleTime = -1;
crt_PT_912025_IR_Temperature_32.SamplingMode = 'Sample based';
crt_PT_912025_IR_Temperature_32.InitialValue = '';

% Frame RT_IRTemp_Temp_31, 9510693 (0x911f25)
% Signal crt_PT_911f25_IR_Temperature_31
crt_PT_911f25_IR_Temperature_31 = Simulink.Signal;
crt_PT_911f25_IR_Temperature_31.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911f25_IR_Temperature_31.RTWInfo.Alias = '';
crt_PT_911f25_IR_Temperature_31.Description = ...
  ['Frame: RT_IRTemp_Temp_31, 9510693 (0x911f25).' char(10) ...
   'Signal: IR_Temperature_31.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911f25_IR_Temperature_31.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911f25_IR_Temperature_31.Min = 0.0;
crt_PT_911f25_IR_Temperature_31.Max = 0.0;
crt_PT_911f25_IR_Temperature_31.DocUnits = '';
crt_PT_911f25_IR_Temperature_31.Dimensions = 1;
crt_PT_911f25_IR_Temperature_31.Complexity = 'real';
crt_PT_911f25_IR_Temperature_31.SampleTime = -1;
crt_PT_911f25_IR_Temperature_31.SamplingMode = 'Sample based';
crt_PT_911f25_IR_Temperature_31.InitialValue = '';

% Frame RT_IRTemp_Temp_29, 9510181 (0x911d25)
% Signal crt_PT_911d25_IR_Temperature_29
crt_PT_911d25_IR_Temperature_29 = Simulink.Signal;
crt_PT_911d25_IR_Temperature_29.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911d25_IR_Temperature_29.RTWInfo.Alias = '';
crt_PT_911d25_IR_Temperature_29.Description = ...
  ['Frame: RT_IRTemp_Temp_29, 9510181 (0x911d25).' char(10) ...
   'Signal: IR_Temperature_29.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911d25_IR_Temperature_29.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911d25_IR_Temperature_29.Min = 0.0;
crt_PT_911d25_IR_Temperature_29.Max = 0.0;
crt_PT_911d25_IR_Temperature_29.DocUnits = '';
crt_PT_911d25_IR_Temperature_29.Dimensions = 1;
crt_PT_911d25_IR_Temperature_29.Complexity = 'real';
crt_PT_911d25_IR_Temperature_29.SampleTime = -1;
crt_PT_911d25_IR_Temperature_29.SamplingMode = 'Sample based';
crt_PT_911d25_IR_Temperature_29.InitialValue = '';

% Frame RT_IRTemp_Temp_28, 9509925 (0x911c25)
% Signal crt_PT_911c25_IR_Temperature_28
crt_PT_911c25_IR_Temperature_28 = Simulink.Signal;
crt_PT_911c25_IR_Temperature_28.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911c25_IR_Temperature_28.RTWInfo.Alias = '';
crt_PT_911c25_IR_Temperature_28.Description = ...
  ['Frame: RT_IRTemp_Temp_28, 9509925 (0x911c25).' char(10) ...
   'Signal: IR_Temperature_28.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911c25_IR_Temperature_28.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911c25_IR_Temperature_28.Min = 0.0;
crt_PT_911c25_IR_Temperature_28.Max = 0.0;
crt_PT_911c25_IR_Temperature_28.DocUnits = '';
crt_PT_911c25_IR_Temperature_28.Dimensions = 1;
crt_PT_911c25_IR_Temperature_28.Complexity = 'real';
crt_PT_911c25_IR_Temperature_28.SampleTime = -1;
crt_PT_911c25_IR_Temperature_28.SamplingMode = 'Sample based';
crt_PT_911c25_IR_Temperature_28.InitialValue = '';

% Frame RT_IRTemp_Temp_27, 9509669 (0x911b25)
% Signal crt_PT_911b25_IR_Temperature_27
crt_PT_911b25_IR_Temperature_27 = Simulink.Signal;
crt_PT_911b25_IR_Temperature_27.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911b25_IR_Temperature_27.RTWInfo.Alias = '';
crt_PT_911b25_IR_Temperature_27.Description = ...
  ['Frame: RT_IRTemp_Temp_27, 9509669 (0x911b25).' char(10) ...
   'Signal: IR_Temperature_27.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911b25_IR_Temperature_27.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911b25_IR_Temperature_27.Min = 0.0;
crt_PT_911b25_IR_Temperature_27.Max = 0.0;
crt_PT_911b25_IR_Temperature_27.DocUnits = '';
crt_PT_911b25_IR_Temperature_27.Dimensions = 1;
crt_PT_911b25_IR_Temperature_27.Complexity = 'real';
crt_PT_911b25_IR_Temperature_27.SampleTime = -1;
crt_PT_911b25_IR_Temperature_27.SamplingMode = 'Sample based';
crt_PT_911b25_IR_Temperature_27.InitialValue = '';

% Frame RT_IRTemp_Temp_25, 9509157 (0x911925)
% Signal crt_PT_911925_IR_Temperature_25
crt_PT_911925_IR_Temperature_25 = Simulink.Signal;
crt_PT_911925_IR_Temperature_25.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911925_IR_Temperature_25.RTWInfo.Alias = '';
crt_PT_911925_IR_Temperature_25.Description = ...
  ['Frame: RT_IRTemp_Temp_25, 9509157 (0x911925).' char(10) ...
   'Signal: IR_Temperature_25.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911925_IR_Temperature_25.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911925_IR_Temperature_25.Min = 0.0;
crt_PT_911925_IR_Temperature_25.Max = 0.0;
crt_PT_911925_IR_Temperature_25.DocUnits = '';
crt_PT_911925_IR_Temperature_25.Dimensions = 1;
crt_PT_911925_IR_Temperature_25.Complexity = 'real';
crt_PT_911925_IR_Temperature_25.SampleTime = -1;
crt_PT_911925_IR_Temperature_25.SamplingMode = 'Sample based';
crt_PT_911925_IR_Temperature_25.InitialValue = '';

% Frame RT_IRTemp_Temp_24, 9508901 (0x911825)
% Signal crt_PT_911825_IR_Temperature_24
crt_PT_911825_IR_Temperature_24 = Simulink.Signal;
crt_PT_911825_IR_Temperature_24.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911825_IR_Temperature_24.RTWInfo.Alias = '';
crt_PT_911825_IR_Temperature_24.Description = ...
  ['Frame: RT_IRTemp_Temp_24, 9508901 (0x911825).' char(10) ...
   'Signal: IR_Temperature_24.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911825_IR_Temperature_24.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911825_IR_Temperature_24.Min = 0.0;
crt_PT_911825_IR_Temperature_24.Max = 0.0;
crt_PT_911825_IR_Temperature_24.DocUnits = '';
crt_PT_911825_IR_Temperature_24.Dimensions = 1;
crt_PT_911825_IR_Temperature_24.Complexity = 'real';
crt_PT_911825_IR_Temperature_24.SampleTime = -1;
crt_PT_911825_IR_Temperature_24.SamplingMode = 'Sample based';
crt_PT_911825_IR_Temperature_24.InitialValue = '';

% Frame RT_IRTemp_Temp_22, 9508389 (0x911625)
% Signal crt_PT_911625_IR_Temperature_22
crt_PT_911625_IR_Temperature_22 = Simulink.Signal;
crt_PT_911625_IR_Temperature_22.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911625_IR_Temperature_22.RTWInfo.Alias = '';
crt_PT_911625_IR_Temperature_22.Description = ...
  ['Frame: RT_IRTemp_Temp_22, 9508389 (0x911625).' char(10) ...
   'Signal: IR_Temperature_22.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911625_IR_Temperature_22.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911625_IR_Temperature_22.Min = 0.0;
crt_PT_911625_IR_Temperature_22.Max = 0.0;
crt_PT_911625_IR_Temperature_22.DocUnits = '';
crt_PT_911625_IR_Temperature_22.Dimensions = 1;
crt_PT_911625_IR_Temperature_22.Complexity = 'real';
crt_PT_911625_IR_Temperature_22.SampleTime = -1;
crt_PT_911625_IR_Temperature_22.SamplingMode = 'Sample based';
crt_PT_911625_IR_Temperature_22.InitialValue = '';

% Frame RT_IRTemp_Temp_23, 9508645 (0x911725)
% Signal crt_PT_911725_IR_Temperature_23
crt_PT_911725_IR_Temperature_23 = Simulink.Signal;
crt_PT_911725_IR_Temperature_23.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911725_IR_Temperature_23.RTWInfo.Alias = '';
crt_PT_911725_IR_Temperature_23.Description = ...
  ['Frame: RT_IRTemp_Temp_23, 9508645 (0x911725).' char(10) ...
   'Signal: IR_Temperature_23.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911725_IR_Temperature_23.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911725_IR_Temperature_23.Min = 0.0;
crt_PT_911725_IR_Temperature_23.Max = 0.0;
crt_PT_911725_IR_Temperature_23.DocUnits = '';
crt_PT_911725_IR_Temperature_23.Dimensions = 1;
crt_PT_911725_IR_Temperature_23.Complexity = 'real';
crt_PT_911725_IR_Temperature_23.SampleTime = -1;
crt_PT_911725_IR_Temperature_23.SamplingMode = 'Sample based';
crt_PT_911725_IR_Temperature_23.InitialValue = '';

% Frame RT_IRTemp_Temp_21, 9508133 (0x911525)
% Signal crt_PT_911525_IR_Temperature_21
crt_PT_911525_IR_Temperature_21 = Simulink.Signal;
crt_PT_911525_IR_Temperature_21.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911525_IR_Temperature_21.RTWInfo.Alias = '';
crt_PT_911525_IR_Temperature_21.Description = ...
  ['Frame: RT_IRTemp_Temp_21, 9508133 (0x911525).' char(10) ...
   'Signal: IR_Temperature_21.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911525_IR_Temperature_21.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911525_IR_Temperature_21.Min = 0.0;
crt_PT_911525_IR_Temperature_21.Max = 0.0;
crt_PT_911525_IR_Temperature_21.DocUnits = '';
crt_PT_911525_IR_Temperature_21.Dimensions = 1;
crt_PT_911525_IR_Temperature_21.Complexity = 'real';
crt_PT_911525_IR_Temperature_21.SampleTime = -1;
crt_PT_911525_IR_Temperature_21.SamplingMode = 'Sample based';
crt_PT_911525_IR_Temperature_21.InitialValue = '';

% Frame RT_IRTemp_Temp_20, 9507877 (0x911425)
% Signal crt_PT_911425_IR_Temperature_20
crt_PT_911425_IR_Temperature_20 = Simulink.Signal;
crt_PT_911425_IR_Temperature_20.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911425_IR_Temperature_20.RTWInfo.Alias = '';
crt_PT_911425_IR_Temperature_20.Description = ...
  ['Frame: RT_IRTemp_Temp_20, 9507877 (0x911425).' char(10) ...
   'Signal: IR_Temperature_20.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911425_IR_Temperature_20.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911425_IR_Temperature_20.Min = 0.0;
crt_PT_911425_IR_Temperature_20.Max = 0.0;
crt_PT_911425_IR_Temperature_20.DocUnits = '';
crt_PT_911425_IR_Temperature_20.Dimensions = 1;
crt_PT_911425_IR_Temperature_20.Complexity = 'real';
crt_PT_911425_IR_Temperature_20.SampleTime = -1;
crt_PT_911425_IR_Temperature_20.SamplingMode = 'Sample based';
crt_PT_911425_IR_Temperature_20.InitialValue = '';

% Frame RT_IRTemp_Temp_19, 9507621 (0x911325)
% Signal crt_PT_911325_IR_Temperature_19
crt_PT_911325_IR_Temperature_19 = Simulink.Signal;
crt_PT_911325_IR_Temperature_19.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911325_IR_Temperature_19.RTWInfo.Alias = '';
crt_PT_911325_IR_Temperature_19.Description = ...
  ['Frame: RT_IRTemp_Temp_19, 9507621 (0x911325).' char(10) ...
   'Signal: IR_Temperature_19.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911325_IR_Temperature_19.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911325_IR_Temperature_19.Min = 0.0;
crt_PT_911325_IR_Temperature_19.Max = 0.0;
crt_PT_911325_IR_Temperature_19.DocUnits = '';
crt_PT_911325_IR_Temperature_19.Dimensions = 1;
crt_PT_911325_IR_Temperature_19.Complexity = 'real';
crt_PT_911325_IR_Temperature_19.SampleTime = -1;
crt_PT_911325_IR_Temperature_19.SamplingMode = 'Sample based';
crt_PT_911325_IR_Temperature_19.InitialValue = '';

% Frame RT_IRTemp_Temp_18, 9507365 (0x911225)
% Signal crt_PT_911225_IR_Temperature_18
crt_PT_911225_IR_Temperature_18 = Simulink.Signal;
crt_PT_911225_IR_Temperature_18.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911225_IR_Temperature_18.RTWInfo.Alias = '';
crt_PT_911225_IR_Temperature_18.Description = ...
  ['Frame: RT_IRTemp_Temp_18, 9507365 (0x911225).' char(10) ...
   'Signal: IR_Temperature_18.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911225_IR_Temperature_18.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911225_IR_Temperature_18.Min = 0.0;
crt_PT_911225_IR_Temperature_18.Max = 0.0;
crt_PT_911225_IR_Temperature_18.DocUnits = '';
crt_PT_911225_IR_Temperature_18.Dimensions = 1;
crt_PT_911225_IR_Temperature_18.Complexity = 'real';
crt_PT_911225_IR_Temperature_18.SampleTime = -1;
crt_PT_911225_IR_Temperature_18.SamplingMode = 'Sample based';
crt_PT_911225_IR_Temperature_18.InitialValue = '';

% Frame RT_IRTemp_Temp_16, 9506853 (0x911025)
% Signal crt_PT_911025_IR_Temperature_16
crt_PT_911025_IR_Temperature_16 = Simulink.Signal;
crt_PT_911025_IR_Temperature_16.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911025_IR_Temperature_16.RTWInfo.Alias = '';
crt_PT_911025_IR_Temperature_16.Description = ...
  ['Frame: RT_IRTemp_Temp_16, 9506853 (0x911025).' char(10) ...
   'Signal: IR_Temperature_16.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911025_IR_Temperature_16.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911025_IR_Temperature_16.Min = 0.0;
crt_PT_911025_IR_Temperature_16.Max = 0.0;
crt_PT_911025_IR_Temperature_16.DocUnits = '';
crt_PT_911025_IR_Temperature_16.Dimensions = 1;
crt_PT_911025_IR_Temperature_16.Complexity = 'real';
crt_PT_911025_IR_Temperature_16.SampleTime = -1;
crt_PT_911025_IR_Temperature_16.SamplingMode = 'Sample based';
crt_PT_911025_IR_Temperature_16.InitialValue = '';

% Frame RT_IRTemp_Temp_15, 9506597 (0x910f25)
% Signal crt_PT_910f25_IR_Temperature_15
crt_PT_910f25_IR_Temperature_15 = Simulink.Signal;
crt_PT_910f25_IR_Temperature_15.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910f25_IR_Temperature_15.RTWInfo.Alias = '';
crt_PT_910f25_IR_Temperature_15.Description = ...
  ['Frame: RT_IRTemp_Temp_15, 9506597 (0x910f25).' char(10) ...
   'Signal: IR_Temperature_15.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910f25_IR_Temperature_15.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910f25_IR_Temperature_15.Min = 0.0;
crt_PT_910f25_IR_Temperature_15.Max = 0.0;
crt_PT_910f25_IR_Temperature_15.DocUnits = '';
crt_PT_910f25_IR_Temperature_15.Dimensions = 1;
crt_PT_910f25_IR_Temperature_15.Complexity = 'real';
crt_PT_910f25_IR_Temperature_15.SampleTime = -1;
crt_PT_910f25_IR_Temperature_15.SamplingMode = 'Sample based';
crt_PT_910f25_IR_Temperature_15.InitialValue = '';

% Frame RT_IRTemp_Temp_14, 9506341 (0x910e25)
% Signal crt_PT_910e25_IR_Temperature_14
crt_PT_910e25_IR_Temperature_14 = Simulink.Signal;
crt_PT_910e25_IR_Temperature_14.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910e25_IR_Temperature_14.RTWInfo.Alias = '';
crt_PT_910e25_IR_Temperature_14.Description = ...
  ['Frame: RT_IRTemp_Temp_14, 9506341 (0x910e25).' char(10) ...
   'Signal: IR_Temperature_14.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910e25_IR_Temperature_14.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910e25_IR_Temperature_14.Min = 0.0;
crt_PT_910e25_IR_Temperature_14.Max = 0.0;
crt_PT_910e25_IR_Temperature_14.DocUnits = '';
crt_PT_910e25_IR_Temperature_14.Dimensions = 1;
crt_PT_910e25_IR_Temperature_14.Complexity = 'real';
crt_PT_910e25_IR_Temperature_14.SampleTime = -1;
crt_PT_910e25_IR_Temperature_14.SamplingMode = 'Sample based';
crt_PT_910e25_IR_Temperature_14.InitialValue = '';

% Frame RT_IRTemp_Temp_13, 9506085 (0x910d25)
% Signal crt_PT_910d25_IR_Temperature_13
crt_PT_910d25_IR_Temperature_13 = Simulink.Signal;
crt_PT_910d25_IR_Temperature_13.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910d25_IR_Temperature_13.RTWInfo.Alias = '';
crt_PT_910d25_IR_Temperature_13.Description = ...
  ['Frame: RT_IRTemp_Temp_13, 9506085 (0x910d25).' char(10) ...
   'Signal: IR_Temperature_13.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910d25_IR_Temperature_13.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910d25_IR_Temperature_13.Min = 0.0;
crt_PT_910d25_IR_Temperature_13.Max = 0.0;
crt_PT_910d25_IR_Temperature_13.DocUnits = '';
crt_PT_910d25_IR_Temperature_13.Dimensions = 1;
crt_PT_910d25_IR_Temperature_13.Complexity = 'real';
crt_PT_910d25_IR_Temperature_13.SampleTime = -1;
crt_PT_910d25_IR_Temperature_13.SamplingMode = 'Sample based';
crt_PT_910d25_IR_Temperature_13.InitialValue = '';

% Frame RT_IRTemp_Temp_12, 9505829 (0x910c25)
% Signal crt_PT_910c25_IR_Temperature_12
crt_PT_910c25_IR_Temperature_12 = Simulink.Signal;
crt_PT_910c25_IR_Temperature_12.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910c25_IR_Temperature_12.RTWInfo.Alias = '';
crt_PT_910c25_IR_Temperature_12.Description = ...
  ['Frame: RT_IRTemp_Temp_12, 9505829 (0x910c25).' char(10) ...
   'Signal: IR_Temperature_12.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910c25_IR_Temperature_12.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910c25_IR_Temperature_12.Min = 0.0;
crt_PT_910c25_IR_Temperature_12.Max = 0.0;
crt_PT_910c25_IR_Temperature_12.DocUnits = '';
crt_PT_910c25_IR_Temperature_12.Dimensions = 1;
crt_PT_910c25_IR_Temperature_12.Complexity = 'real';
crt_PT_910c25_IR_Temperature_12.SampleTime = -1;
crt_PT_910c25_IR_Temperature_12.SamplingMode = 'Sample based';
crt_PT_910c25_IR_Temperature_12.InitialValue = '';

% Frame RT_IRTemp_Temp_11, 9505573 (0x910b25)
% Signal crt_PT_910b25_IR_Temperature_11
crt_PT_910b25_IR_Temperature_11 = Simulink.Signal;
crt_PT_910b25_IR_Temperature_11.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910b25_IR_Temperature_11.RTWInfo.Alias = '';
crt_PT_910b25_IR_Temperature_11.Description = ...
  ['Frame: RT_IRTemp_Temp_11, 9505573 (0x910b25).' char(10) ...
   'Signal: IR_Temperature_11.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910b25_IR_Temperature_11.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910b25_IR_Temperature_11.Min = 0.0;
crt_PT_910b25_IR_Temperature_11.Max = 0.0;
crt_PT_910b25_IR_Temperature_11.DocUnits = '';
crt_PT_910b25_IR_Temperature_11.Dimensions = 1;
crt_PT_910b25_IR_Temperature_11.Complexity = 'real';
crt_PT_910b25_IR_Temperature_11.SampleTime = -1;
crt_PT_910b25_IR_Temperature_11.SamplingMode = 'Sample based';
crt_PT_910b25_IR_Temperature_11.InitialValue = '';

% Frame RT_IRTemp_Temp_10, 9505317 (0x910a25)
% Signal crt_PT_910a25_IR_Temperature_10
crt_PT_910a25_IR_Temperature_10 = Simulink.Signal;
crt_PT_910a25_IR_Temperature_10.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910a25_IR_Temperature_10.RTWInfo.Alias = '';
crt_PT_910a25_IR_Temperature_10.Description = ...
  ['Frame: RT_IRTemp_Temp_10, 9505317 (0x910a25).' char(10) ...
   'Signal: IR_Temperature_10.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910a25_IR_Temperature_10.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910a25_IR_Temperature_10.Min = 0.0;
crt_PT_910a25_IR_Temperature_10.Max = 0.0;
crt_PT_910a25_IR_Temperature_10.DocUnits = '';
crt_PT_910a25_IR_Temperature_10.Dimensions = 1;
crt_PT_910a25_IR_Temperature_10.Complexity = 'real';
crt_PT_910a25_IR_Temperature_10.SampleTime = -1;
crt_PT_910a25_IR_Temperature_10.SamplingMode = 'Sample based';
crt_PT_910a25_IR_Temperature_10.InitialValue = '';

% Frame RT_IRTemp_Temp_8, 9504805 (0x910825)
% Signal crt_PT_910825_IR_Temperature_8
crt_PT_910825_IR_Temperature_8 = Simulink.Signal;
crt_PT_910825_IR_Temperature_8.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910825_IR_Temperature_8.RTWInfo.Alias = '';
crt_PT_910825_IR_Temperature_8.Description = ...
  ['Frame: RT_IRTemp_Temp_8, 9504805 (0x910825).' char(10) ...
   'Signal: IR_Temperature_8.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910825_IR_Temperature_8.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910825_IR_Temperature_8.Min = 0.0;
crt_PT_910825_IR_Temperature_8.Max = 0.0;
crt_PT_910825_IR_Temperature_8.DocUnits = '';
crt_PT_910825_IR_Temperature_8.Dimensions = 1;
crt_PT_910825_IR_Temperature_8.Complexity = 'real';
crt_PT_910825_IR_Temperature_8.SampleTime = -1;
crt_PT_910825_IR_Temperature_8.SamplingMode = 'Sample based';
crt_PT_910825_IR_Temperature_8.InitialValue = '';

% Frame RT_IRTemp_Temp_9, 9505061 (0x910925)
% Signal crt_PT_910925_IR_Temperature_9
crt_PT_910925_IR_Temperature_9 = Simulink.Signal;
crt_PT_910925_IR_Temperature_9.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910925_IR_Temperature_9.RTWInfo.Alias = '';
crt_PT_910925_IR_Temperature_9.Description = ...
  ['Frame: RT_IRTemp_Temp_9, 9505061 (0x910925).' char(10) ...
   'Signal: IR_Temperature_9.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910925_IR_Temperature_9.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910925_IR_Temperature_9.Min = 0.0;
crt_PT_910925_IR_Temperature_9.Max = 0.0;
crt_PT_910925_IR_Temperature_9.DocUnits = '';
crt_PT_910925_IR_Temperature_9.Dimensions = 1;
crt_PT_910925_IR_Temperature_9.Complexity = 'real';
crt_PT_910925_IR_Temperature_9.SampleTime = -1;
crt_PT_910925_IR_Temperature_9.SamplingMode = 'Sample based';
crt_PT_910925_IR_Temperature_9.InitialValue = '';

% Frame RT_IRTemp_Temp_17, 9507109 (0x911125)
% Signal crt_PT_911125_IR_Temperature_17
crt_PT_911125_IR_Temperature_17 = Simulink.Signal;
crt_PT_911125_IR_Temperature_17.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911125_IR_Temperature_17.RTWInfo.Alias = '';
crt_PT_911125_IR_Temperature_17.Description = ...
  ['Frame: RT_IRTemp_Temp_17, 9507109 (0x911125).' char(10) ...
   'Signal: IR_Temperature_17.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911125_IR_Temperature_17.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911125_IR_Temperature_17.Min = 0.0;
crt_PT_911125_IR_Temperature_17.Max = 0.0;
crt_PT_911125_IR_Temperature_17.DocUnits = '';
crt_PT_911125_IR_Temperature_17.Dimensions = 1;
crt_PT_911125_IR_Temperature_17.Complexity = 'real';
crt_PT_911125_IR_Temperature_17.SampleTime = -1;
crt_PT_911125_IR_Temperature_17.SamplingMode = 'Sample based';
crt_PT_911125_IR_Temperature_17.InitialValue = '';

% Frame RT_IRTemp_Temp_6, 9504293 (0x910625)
% Signal crt_PT_910625_IR_Temperature_6
crt_PT_910625_IR_Temperature_6 = Simulink.Signal;
crt_PT_910625_IR_Temperature_6.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910625_IR_Temperature_6.RTWInfo.Alias = '';
crt_PT_910625_IR_Temperature_6.Description = ...
  ['Frame: RT_IRTemp_Temp_6, 9504293 (0x910625).' char(10) ...
   'Signal: IR_Temperature_6.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910625_IR_Temperature_6.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910625_IR_Temperature_6.Min = 0.0;
crt_PT_910625_IR_Temperature_6.Max = 0.0;
crt_PT_910625_IR_Temperature_6.DocUnits = '';
crt_PT_910625_IR_Temperature_6.Dimensions = 1;
crt_PT_910625_IR_Temperature_6.Complexity = 'real';
crt_PT_910625_IR_Temperature_6.SampleTime = -1;
crt_PT_910625_IR_Temperature_6.SamplingMode = 'Sample based';
crt_PT_910625_IR_Temperature_6.InitialValue = '';

% Frame RT_IRTemp_Temp_5, 9504037 (0x910525)
% Signal crt_PT_910525_IR_Temperature_5
crt_PT_910525_IR_Temperature_5 = Simulink.Signal;
crt_PT_910525_IR_Temperature_5.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910525_IR_Temperature_5.RTWInfo.Alias = '';
crt_PT_910525_IR_Temperature_5.Description = ...
  ['Frame: RT_IRTemp_Temp_5, 9504037 (0x910525).' char(10) ...
   'Signal: IR_Temperature_5.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910525_IR_Temperature_5.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910525_IR_Temperature_5.Min = 0.0;
crt_PT_910525_IR_Temperature_5.Max = 0.0;
crt_PT_910525_IR_Temperature_5.DocUnits = '';
crt_PT_910525_IR_Temperature_5.Dimensions = 1;
crt_PT_910525_IR_Temperature_5.Complexity = 'real';
crt_PT_910525_IR_Temperature_5.SampleTime = -1;
crt_PT_910525_IR_Temperature_5.SamplingMode = 'Sample based';
crt_PT_910525_IR_Temperature_5.InitialValue = '';

% Frame RT_IRTemp_Temp_4, 9503781 (0x910425)
% Signal crt_PT_910425_IR_Temperature_4
crt_PT_910425_IR_Temperature_4 = Simulink.Signal;
crt_PT_910425_IR_Temperature_4.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910425_IR_Temperature_4.RTWInfo.Alias = '';
crt_PT_910425_IR_Temperature_4.Description = ...
  ['Frame: RT_IRTemp_Temp_4, 9503781 (0x910425).' char(10) ...
   'Signal: IR_Temperature_4.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910425_IR_Temperature_4.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910425_IR_Temperature_4.Min = 0.0;
crt_PT_910425_IR_Temperature_4.Max = 0.0;
crt_PT_910425_IR_Temperature_4.DocUnits = '';
crt_PT_910425_IR_Temperature_4.Dimensions = 1;
crt_PT_910425_IR_Temperature_4.Complexity = 'real';
crt_PT_910425_IR_Temperature_4.SampleTime = -1;
crt_PT_910425_IR_Temperature_4.SamplingMode = 'Sample based';
crt_PT_910425_IR_Temperature_4.InitialValue = '';

% Frame RT_IRTemp_Temp_3, 9503525 (0x910325)
% Signal crt_PT_910325_IR_Temperature_3
crt_PT_910325_IR_Temperature_3 = Simulink.Signal;
crt_PT_910325_IR_Temperature_3.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910325_IR_Temperature_3.RTWInfo.Alias = '';
crt_PT_910325_IR_Temperature_3.Description = ...
  ['Frame: RT_IRTemp_Temp_3, 9503525 (0x910325).' char(10) ...
   'Signal: IR_Temperature_3.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910325_IR_Temperature_3.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910325_IR_Temperature_3.Min = 0.0;
crt_PT_910325_IR_Temperature_3.Max = 0.0;
crt_PT_910325_IR_Temperature_3.DocUnits = '';
crt_PT_910325_IR_Temperature_3.Dimensions = 1;
crt_PT_910325_IR_Temperature_3.Complexity = 'real';
crt_PT_910325_IR_Temperature_3.SampleTime = -1;
crt_PT_910325_IR_Temperature_3.SamplingMode = 'Sample based';
crt_PT_910325_IR_Temperature_3.InitialValue = '';

% Frame RT_IRTemp_Temp_2, 9503269 (0x910225)
% Signal crt_PT_910225_IR_Temperature_2
crt_PT_910225_IR_Temperature_2 = Simulink.Signal;
crt_PT_910225_IR_Temperature_2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910225_IR_Temperature_2.RTWInfo.Alias = '';
crt_PT_910225_IR_Temperature_2.Description = ...
  ['Frame: RT_IRTemp_Temp_2, 9503269 (0x910225).' char(10) ...
   'Signal: IR_Temperature_2.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910225_IR_Temperature_2.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910225_IR_Temperature_2.Min = 0.0;
crt_PT_910225_IR_Temperature_2.Max = 0.0;
crt_PT_910225_IR_Temperature_2.DocUnits = '';
crt_PT_910225_IR_Temperature_2.Dimensions = 1;
crt_PT_910225_IR_Temperature_2.Complexity = 'real';
crt_PT_910225_IR_Temperature_2.SampleTime = -1;
crt_PT_910225_IR_Temperature_2.SamplingMode = 'Sample based';
crt_PT_910225_IR_Temperature_2.InitialValue = '';

% Frame RT_IRTemp_Temp_1, 9503013 (0x910125)
% Signal crt_PT_910125_IR_Temperature_1
crt_PT_910125_IR_Temperature_1 = Simulink.Signal;
crt_PT_910125_IR_Temperature_1.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910125_IR_Temperature_1.RTWInfo.Alias = '';
crt_PT_910125_IR_Temperature_1.Description = ...
  ['Frame: RT_IRTemp_Temp_1, 9503013 (0x910125).' char(10) ...
   'Signal: IR_Temperature_1.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910125_IR_Temperature_1.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910125_IR_Temperature_1.Min = 0.0;
crt_PT_910125_IR_Temperature_1.Max = 0.0;
crt_PT_910125_IR_Temperature_1.DocUnits = '';
crt_PT_910125_IR_Temperature_1.Dimensions = 1;
crt_PT_910125_IR_Temperature_1.Complexity = 'real';
crt_PT_910125_IR_Temperature_1.SampleTime = -1;
crt_PT_910125_IR_Temperature_1.SamplingMode = 'Sample based';
crt_PT_910125_IR_Temperature_1.InitialValue = '';
% Signal crt_PT_910125_CRC
crt_PT_910125_CRC = Simulink.Signal;
crt_PT_910125_CRC.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910125_CRC.RTWInfo.Alias = '';
crt_PT_910125_CRC.Description = ...
  ['Checksum' char(10) ...
   'Frame: RT_IRTemp_Temp_1, 9503013 (0x910125).' char(10) ...
   'Signal: CRC.' char(10) ...
   'Range (world values): 1.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_910125_CRC.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_910125_CRC.Min = 1.0;
crt_PT_910125_CRC.Max = 255.0;
crt_PT_910125_CRC.DocUnits = '';
crt_PT_910125_CRC.Dimensions = 1;
crt_PT_910125_CRC.Complexity = 'real';
crt_PT_910125_CRC.SampleTime = -1;
crt_PT_910125_CRC.SamplingMode = 'Sample based';
crt_PT_910125_CRC.InitialValue = '';

% Frame RT_SB_Trig_Final_Condition, 9242402 (0x8d0722)
% Signal crt_PT_8d0722_Validity_Final_Speed
crt_PT_8d0722_Validity_Final_Speed = Simulink.Signal;
crt_PT_8d0722_Validity_Final_Speed.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0722_Validity_Final_Speed.RTWInfo.Alias = '';
crt_PT_8d0722_Validity_Final_Speed.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Trig_Final_Condition, 9242402 (0x8d0722).' char(10) ...
   'Signal: Validity_Final_Speed.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8d0722_Validity_Final_Speed.DataType = 'boolean';
crt_PT_8d0722_Validity_Final_Speed.Min = 0.0;
crt_PT_8d0722_Validity_Final_Speed.Max = 1.0;
crt_PT_8d0722_Validity_Final_Speed.DocUnits = '';
crt_PT_8d0722_Validity_Final_Speed.Dimensions = 1;
crt_PT_8d0722_Validity_Final_Speed.Complexity = 'real';
crt_PT_8d0722_Validity_Final_Speed.SampleTime = -1;
crt_PT_8d0722_Validity_Final_Speed.SamplingMode = 'Sample based';
crt_PT_8d0722_Validity_Final_Speed.InitialValue = '';
% Signal crt_PT_8d0722_Final_Speed
crt_PT_8d0722_Final_Speed = Simulink.Signal;
crt_PT_8d0722_Final_Speed.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0722_Final_Speed.RTWInfo.Alias = '';
crt_PT_8d0722_Final_Speed.Description = ...
  ['Speed at end of triggered test' char(10) ...
   'Frame: RT_SB_Trig_Final_Condition, 9242402 (0x8d0722).' char(10) ...
   'Signal: Final_Speed.' char(10) ...
   'Range (world values): 0.0 ... 1675.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8d0722_Final_Speed.DataType = 'fixdt(0, 32, 1.0E-4, 0.0)';
crt_PT_8d0722_Final_Speed.Min = 0.0;
crt_PT_8d0722_Final_Speed.Max = 1675.0;
crt_PT_8d0722_Final_Speed.DocUnits = 'm/s';
crt_PT_8d0722_Final_Speed.Dimensions = 1;
crt_PT_8d0722_Final_Speed.Complexity = 'real';
crt_PT_8d0722_Final_Speed.SampleTime = -1;
crt_PT_8d0722_Final_Speed.SamplingMode = 'Sample based';
crt_PT_8d0722_Final_Speed.InitialValue = '';

% Frame RT_SB_Trig_Initial_Condition, 794 (0x31a)
% Signal crt_PT_31a_Validity_Initial_Speed
crt_PT_31a_Validity_Initial_Speed = Simulink.Signal;
crt_PT_31a_Validity_Initial_Speed.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_31a_Validity_Initial_Speed.RTWInfo.Alias = '';
crt_PT_31a_Validity_Initial_Speed.Description = ...
  ['Valid when bit is set, invalid when bit is clear. Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Trig_Initial_Condition, 794 (0x31a).' char(10) ...
   'Signal: Validity_Initial_Speed.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_31a_Validity_Initial_Speed.DataType = 'boolean';
crt_PT_31a_Validity_Initial_Speed.Min = 0.0;
crt_PT_31a_Validity_Initial_Speed.Max = 1.0;
crt_PT_31a_Validity_Initial_Speed.DocUnits = '';
crt_PT_31a_Validity_Initial_Speed.Dimensions = 1;
crt_PT_31a_Validity_Initial_Speed.Complexity = 'real';
crt_PT_31a_Validity_Initial_Speed.SampleTime = -1;
crt_PT_31a_Validity_Initial_Speed.SamplingMode = 'Sample based';
crt_PT_31a_Validity_Initial_Speed.InitialValue = '';
% Signal crt_PT_31a_Validity_Initial_Heading
crt_PT_31a_Validity_Initial_Heading = Simulink.Signal;
crt_PT_31a_Validity_Initial_Heading.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_31a_Validity_Initial_Heading.RTWInfo.Alias = '';
crt_PT_31a_Validity_Initial_Heading.Description = ...
  ['Valid when bit is set, invalid when bit is clear. Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Trig_Initial_Condition, 794 (0x31a).' char(10) ...
   'Signal: Validity_Initial_Heading.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_31a_Validity_Initial_Heading.DataType = 'boolean';
crt_PT_31a_Validity_Initial_Heading.Min = 0.0;
crt_PT_31a_Validity_Initial_Heading.Max = 1.0;
crt_PT_31a_Validity_Initial_Heading.DocUnits = '';
crt_PT_31a_Validity_Initial_Heading.Dimensions = 1;
crt_PT_31a_Validity_Initial_Heading.Complexity = 'real';
crt_PT_31a_Validity_Initial_Heading.SampleTime = -1;
crt_PT_31a_Validity_Initial_Heading.SamplingMode = 'Sample based';
crt_PT_31a_Validity_Initial_Heading.InitialValue = '';
% Signal crt_PT_31a_Initial_Speed
crt_PT_31a_Initial_Speed = Simulink.Signal;
crt_PT_31a_Initial_Speed.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_31a_Initial_Speed.RTWInfo.Alias = '';
crt_PT_31a_Initial_Speed.Description = ...
  ['Speed at start of triggered test Speed at start of triggered test' char(10) ...
   'Frame: RT_SB_Trig_Initial_Condition, 794 (0x31a).' char(10) ...
   'Signal: Initial_Speed.' char(10) ...
   'Range (world values): 0.0 ... 1675.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_31a_Initial_Speed.DataType = 'fixdt(0, 32, 1.0E-4, 0.0)';
crt_PT_31a_Initial_Speed.Min = 0.0;
crt_PT_31a_Initial_Speed.Max = 1675.0;
crt_PT_31a_Initial_Speed.DocUnits = 'm/s';
crt_PT_31a_Initial_Speed.Dimensions = 1;
crt_PT_31a_Initial_Speed.Complexity = 'real';
crt_PT_31a_Initial_Speed.SampleTime = -1;
crt_PT_31a_Initial_Speed.SamplingMode = 'Sample based';
crt_PT_31a_Initial_Speed.InitialValue = '';
% Signal crt_PT_31a_Initial_Heading
crt_PT_31a_Initial_Heading = Simulink.Signal;
crt_PT_31a_Initial_Heading.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_31a_Initial_Heading.RTWInfo.Alias = '';
crt_PT_31a_Initial_Heading.Description = ...
  ['Heading (track) at start of triggered test Heading (track) at start of triggered test' char(10) ...
   'Frame: RT_SB_Trig_Initial_Condition, 794 (0x31a).' char(10) ...
   'Signal: Initial_Heading.' char(10) ...
   'Range (world values): -180.0 ... 180.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_31a_Initial_Heading.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_31a_Initial_Heading.Min = -180.0;
crt_PT_31a_Initial_Heading.Max = 180.0;
crt_PT_31a_Initial_Heading.DocUnits = 'degrees';
crt_PT_31a_Initial_Heading.Dimensions = 1;
crt_PT_31a_Initial_Heading.Complexity = 'real';
crt_PT_31a_Initial_Heading.SampleTime = -1;
crt_PT_31a_Initial_Heading.SamplingMode = 'Sample based';
crt_PT_31a_Initial_Heading.InitialValue = '';
% Signal crt_PT_31a_MFDD_Start_Threshold
crt_PT_31a_MFDD_Start_Threshold = Simulink.Signal;
crt_PT_31a_MFDD_Start_Threshold.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_31a_MFDD_Start_Threshold.RTWInfo.Alias = '';
crt_PT_31a_MFDD_Start_Threshold.Description = ...
  ['Frame: RT_SB_Trig_Initial_Condition, 794 (0x31a).' char(10) ...
   'Signal: MFDD_Start_Threshold.' char(10) ...
   'Range (world values): 0.0 ... 100.0 [%].' char(10) ...
   'Scaling: WorldValue = BinaryValue [%]' ...
  ];
crt_PT_31a_MFDD_Start_Threshold.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_31a_MFDD_Start_Threshold.Min = 0.0;
crt_PT_31a_MFDD_Start_Threshold.Max = 100.0;
crt_PT_31a_MFDD_Start_Threshold.DocUnits = '%';
crt_PT_31a_MFDD_Start_Threshold.Dimensions = 1;
crt_PT_31a_MFDD_Start_Threshold.Complexity = 'real';
crt_PT_31a_MFDD_Start_Threshold.SampleTime = -1;
crt_PT_31a_MFDD_Start_Threshold.SamplingMode = 'Sample based';
crt_PT_31a_MFDD_Start_Threshold.InitialValue = '';
% Signal crt_PT_31a_MFDD_End_Threshold
crt_PT_31a_MFDD_End_Threshold = Simulink.Signal;
crt_PT_31a_MFDD_End_Threshold.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_31a_MFDD_End_Threshold.RTWInfo.Alias = '';
crt_PT_31a_MFDD_End_Threshold.Description = ...
  ['Frame: RT_SB_Trig_Initial_Condition, 794 (0x31a).' char(10) ...
   'Signal: MFDD_End_Threshold.' char(10) ...
   'Range (world values): 0.0 ... 100.0 [%].' char(10) ...
   'Scaling: WorldValue = BinaryValue [%]' ...
  ];
crt_PT_31a_MFDD_End_Threshold.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_31a_MFDD_End_Threshold.Min = 0.0;
crt_PT_31a_MFDD_End_Threshold.Max = 100.0;
crt_PT_31a_MFDD_End_Threshold.DocUnits = '%';
crt_PT_31a_MFDD_End_Threshold.Dimensions = 1;
crt_PT_31a_MFDD_End_Threshold.Complexity = 'real';
crt_PT_31a_MFDD_End_Threshold.SampleTime = -1;
crt_PT_31a_MFDD_End_Threshold.SamplingMode = 'Sample based';
crt_PT_31a_MFDD_End_Threshold.InitialValue = '';

% Frame RT_SB_Trig_Direct_Dist, 9241890 (0x8d0522)
% Signal crt_PT_8d0522_Direct_Distance
crt_PT_8d0522_Direct_Distance = Simulink.Signal;
crt_PT_8d0522_Direct_Distance.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0522_Direct_Distance.RTWInfo.Alias = '';
crt_PT_8d0522_Direct_Distance.Description = ...
  ['Direct distance from start of test to current position' char(10) ...
   'Frame: RT_SB_Trig_Direct_Dist, 9241890 (0x8d0522).' char(10) ...
   'Signal: Direct_Distance.' char(10) ...
   'Range (world values): 0.0 ... 4294970.0 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8d0522_Direct_Distance.DataType = 'fixdt(0, 32, 0.001, 0.0)';
crt_PT_8d0522_Direct_Distance.Min = 0.0;
crt_PT_8d0522_Direct_Distance.Max = 4294970.0;
crt_PT_8d0522_Direct_Distance.DocUnits = 'm';
crt_PT_8d0522_Direct_Distance.Dimensions = 1;
crt_PT_8d0522_Direct_Distance.Complexity = 'real';
crt_PT_8d0522_Direct_Distance.SampleTime = -1;
crt_PT_8d0522_Direct_Distance.SamplingMode = 'Sample based';
crt_PT_8d0522_Direct_Distance.InitialValue = '';
% Signal crt_PT_8d0522_Path_Distance_2D
crt_PT_8d0522_Path_Distance_2D = Simulink.Signal;
crt_PT_8d0522_Path_Distance_2D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0522_Path_Distance_2D.RTWInfo.Alias = '';
crt_PT_8d0522_Path_Distance_2D.Description = ...
  ['2D path distance (horizontal components only)' char(10) ...
   'Frame: RT_SB_Trig_Direct_Dist, 9241890 (0x8d0522).' char(10) ...
   'Signal: Path_Distance_2D.' char(10) ...
   'Range (world values): 0.0 ... 4294970.0 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8d0522_Path_Distance_2D.DataType = 'fixdt(0, 32, 0.001, 0.0)';
crt_PT_8d0522_Path_Distance_2D.Min = 0.0;
crt_PT_8d0522_Path_Distance_2D.Max = 4294970.0;
crt_PT_8d0522_Path_Distance_2D.DocUnits = 'm';
crt_PT_8d0522_Path_Distance_2D.Dimensions = 1;
crt_PT_8d0522_Path_Distance_2D.Complexity = 'real';
crt_PT_8d0522_Path_Distance_2D.SampleTime = -1;
crt_PT_8d0522_Path_Distance_2D.SamplingMode = 'Sample based';
crt_PT_8d0522_Path_Distance_2D.InitialValue = '';

% Frame RT_SB_Trig_Path_Dist, 9241378 (0x8d0322)
% Signal crt_PT_8d0322_Path_Distance_3D
crt_PT_8d0322_Path_Distance_3D = Simulink.Signal;
crt_PT_8d0322_Path_Distance_3D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0322_Path_Distance_3D.RTWInfo.Alias = '';
crt_PT_8d0322_Path_Distance_3D.Description = ...
  ['3D path distance' char(10) ...
   'Frame: RT_SB_Trig_Path_Dist, 9241378 (0x8d0322).' char(10) ...
   'Signal: Path_Distance_3D.' char(10) ...
   'Range (world values): 0.0 ... 4294970.0 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8d0322_Path_Distance_3D.DataType = 'fixdt(0, 32, 0.001, 0.0)';
crt_PT_8d0322_Path_Distance_3D.Min = 0.0;
crt_PT_8d0322_Path_Distance_3D.Max = 4294970.0;
crt_PT_8d0322_Path_Distance_3D.DocUnits = 'm';
crt_PT_8d0322_Path_Distance_3D.Dimensions = 1;
crt_PT_8d0322_Path_Distance_3D.Complexity = 'real';
crt_PT_8d0322_Path_Distance_3D.SampleTime = -1;
crt_PT_8d0322_Path_Distance_3D.SamplingMode = 'Sample based';
crt_PT_8d0322_Path_Distance_3D.InitialValue = '';

% Frame RT_DL1MK3_Measure_Time_11, 9833252 (0x960b24)
% Signal crt_PT_960b24_Measured_Time_11
crt_PT_960b24_Measured_Time_11 = Simulink.Signal;
crt_PT_960b24_Measured_Time_11.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_960b24_Measured_Time_11.RTWInfo.Alias = '';
crt_PT_960b24_Measured_Time_11.Description = ...
  ['Frame: RT_DL1MK3_Measure_Time_11, 9833252 (0x960b24).' char(10) ...
   'Signal: Measured_Time_11.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_960b24_Measured_Time_11.DataType = 'fixdt(0, 32, 1.0, 0.0)';
crt_PT_960b24_Measured_Time_11.Min = 0.0;
crt_PT_960b24_Measured_Time_11.Max = 0.0;
crt_PT_960b24_Measured_Time_11.DocUnits = '';
crt_PT_960b24_Measured_Time_11.Dimensions = 1;
crt_PT_960b24_Measured_Time_11.Complexity = 'real';
crt_PT_960b24_Measured_Time_11.SampleTime = -1;
crt_PT_960b24_Measured_Time_11.SamplingMode = 'Sample based';
crt_PT_960b24_Measured_Time_11.InitialValue = '';

% Frame RT_DL1MK3_Measure_Time_10, 9832996 (0x960a24)
% Signal crt_PT_960a24_Measured_Time_10
crt_PT_960a24_Measured_Time_10 = Simulink.Signal;
crt_PT_960a24_Measured_Time_10.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_960a24_Measured_Time_10.RTWInfo.Alias = '';
crt_PT_960a24_Measured_Time_10.Description = ...
  ['Frame: RT_DL1MK3_Measure_Time_10, 9832996 (0x960a24).' char(10) ...
   'Signal: Measured_Time_10.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_960a24_Measured_Time_10.DataType = 'fixdt(0, 32, 1.0, 0.0)';
crt_PT_960a24_Measured_Time_10.Min = 0.0;
crt_PT_960a24_Measured_Time_10.Max = 0.0;
crt_PT_960a24_Measured_Time_10.DocUnits = '';
crt_PT_960a24_Measured_Time_10.Dimensions = 1;
crt_PT_960a24_Measured_Time_10.Complexity = 'real';
crt_PT_960a24_Measured_Time_10.SampleTime = -1;
crt_PT_960a24_Measured_Time_10.SamplingMode = 'Sample based';
crt_PT_960a24_Measured_Time_10.InitialValue = '';

% Frame RT_DL1MK3_Measure_Time_9, 9832740 (0x960924)
% Signal crt_PT_960924_Measured_Time_9
crt_PT_960924_Measured_Time_9 = Simulink.Signal;
crt_PT_960924_Measured_Time_9.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_960924_Measured_Time_9.RTWInfo.Alias = '';
crt_PT_960924_Measured_Time_9.Description = ...
  ['Frame: RT_DL1MK3_Measure_Time_9, 9832740 (0x960924).' char(10) ...
   'Signal: Measured_Time_9.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_960924_Measured_Time_9.DataType = 'fixdt(0, 32, 1.0, 0.0)';
crt_PT_960924_Measured_Time_9.Min = 0.0;
crt_PT_960924_Measured_Time_9.Max = 0.0;
crt_PT_960924_Measured_Time_9.DocUnits = '';
crt_PT_960924_Measured_Time_9.Dimensions = 1;
crt_PT_960924_Measured_Time_9.Complexity = 'real';
crt_PT_960924_Measured_Time_9.SampleTime = -1;
crt_PT_960924_Measured_Time_9.SamplingMode = 'Sample based';
crt_PT_960924_Measured_Time_9.InitialValue = '';

% Frame RT_DL1MK3_Measure_Time_8, 9832484 (0x960824)
% Signal crt_PT_960824_Measured_Time_8
crt_PT_960824_Measured_Time_8 = Simulink.Signal;
crt_PT_960824_Measured_Time_8.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_960824_Measured_Time_8.RTWInfo.Alias = '';
crt_PT_960824_Measured_Time_8.Description = ...
  ['Frame: RT_DL1MK3_Measure_Time_8, 9832484 (0x960824).' char(10) ...
   'Signal: Measured_Time_8.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_960824_Measured_Time_8.DataType = 'fixdt(0, 32, 1.0, 0.0)';
crt_PT_960824_Measured_Time_8.Min = 0.0;
crt_PT_960824_Measured_Time_8.Max = 0.0;
crt_PT_960824_Measured_Time_8.DocUnits = '';
crt_PT_960824_Measured_Time_8.Dimensions = 1;
crt_PT_960824_Measured_Time_8.Complexity = 'real';
crt_PT_960824_Measured_Time_8.SampleTime = -1;
crt_PT_960824_Measured_Time_8.SamplingMode = 'Sample based';
crt_PT_960824_Measured_Time_8.InitialValue = '';

% Frame RT_DL1MK3_Measure_Time_7, 9832228 (0x960724)
% Signal crt_PT_960724_Measured_Time_7
crt_PT_960724_Measured_Time_7 = Simulink.Signal;
crt_PT_960724_Measured_Time_7.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_960724_Measured_Time_7.RTWInfo.Alias = '';
crt_PT_960724_Measured_Time_7.Description = ...
  ['Frame: RT_DL1MK3_Measure_Time_7, 9832228 (0x960724).' char(10) ...
   'Signal: Measured_Time_7.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_960724_Measured_Time_7.DataType = 'fixdt(0, 32, 1.0, 0.0)';
crt_PT_960724_Measured_Time_7.Min = 0.0;
crt_PT_960724_Measured_Time_7.Max = 0.0;
crt_PT_960724_Measured_Time_7.DocUnits = '';
crt_PT_960724_Measured_Time_7.Dimensions = 1;
crt_PT_960724_Measured_Time_7.Complexity = 'real';
crt_PT_960724_Measured_Time_7.SampleTime = -1;
crt_PT_960724_Measured_Time_7.SamplingMode = 'Sample based';
crt_PT_960724_Measured_Time_7.InitialValue = '';

% Frame RT_DL1MK3_Measure_Time_6, 9831972 (0x960624)
% Signal crt_PT_960624_Measured_Time_6
crt_PT_960624_Measured_Time_6 = Simulink.Signal;
crt_PT_960624_Measured_Time_6.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_960624_Measured_Time_6.RTWInfo.Alias = '';
crt_PT_960624_Measured_Time_6.Description = ...
  ['Frame: RT_DL1MK3_Measure_Time_6, 9831972 (0x960624).' char(10) ...
   'Signal: Measured_Time_6.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_960624_Measured_Time_6.DataType = 'fixdt(0, 32, 1.0, 0.0)';
crt_PT_960624_Measured_Time_6.Min = 0.0;
crt_PT_960624_Measured_Time_6.Max = 0.0;
crt_PT_960624_Measured_Time_6.DocUnits = '';
crt_PT_960624_Measured_Time_6.Dimensions = 1;
crt_PT_960624_Measured_Time_6.Complexity = 'real';
crt_PT_960624_Measured_Time_6.SampleTime = -1;
crt_PT_960624_Measured_Time_6.SamplingMode = 'Sample based';
crt_PT_960624_Measured_Time_6.InitialValue = '';

% Frame RT_DL1MK3_Measure_Time_5, 9831716 (0x960524)
% Signal crt_PT_960524_Measured_Time_5
crt_PT_960524_Measured_Time_5 = Simulink.Signal;
crt_PT_960524_Measured_Time_5.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_960524_Measured_Time_5.RTWInfo.Alias = '';
crt_PT_960524_Measured_Time_5.Description = ...
  ['Frame: RT_DL1MK3_Measure_Time_5, 9831716 (0x960524).' char(10) ...
   'Signal: Measured_Time_5.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_960524_Measured_Time_5.DataType = 'fixdt(0, 32, 1.0, 0.0)';
crt_PT_960524_Measured_Time_5.Min = 0.0;
crt_PT_960524_Measured_Time_5.Max = 0.0;
crt_PT_960524_Measured_Time_5.DocUnits = '';
crt_PT_960524_Measured_Time_5.Dimensions = 1;
crt_PT_960524_Measured_Time_5.Complexity = 'real';
crt_PT_960524_Measured_Time_5.SampleTime = -1;
crt_PT_960524_Measured_Time_5.SamplingMode = 'Sample based';
crt_PT_960524_Measured_Time_5.InitialValue = '';

% Frame RT_DL1MK3_Measure_Time_4, 9831460 (0x960424)
% Signal crt_PT_960424_Measured_Time_4
crt_PT_960424_Measured_Time_4 = Simulink.Signal;
crt_PT_960424_Measured_Time_4.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_960424_Measured_Time_4.RTWInfo.Alias = '';
crt_PT_960424_Measured_Time_4.Description = ...
  ['Frame: RT_DL1MK3_Measure_Time_4, 9831460 (0x960424).' char(10) ...
   'Signal: Measured_Time_4.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_960424_Measured_Time_4.DataType = 'fixdt(0, 32, 1.0, 0.0)';
crt_PT_960424_Measured_Time_4.Min = 0.0;
crt_PT_960424_Measured_Time_4.Max = 0.0;
crt_PT_960424_Measured_Time_4.DocUnits = '';
crt_PT_960424_Measured_Time_4.Dimensions = 1;
crt_PT_960424_Measured_Time_4.Complexity = 'real';
crt_PT_960424_Measured_Time_4.SampleTime = -1;
crt_PT_960424_Measured_Time_4.SamplingMode = 'Sample based';
crt_PT_960424_Measured_Time_4.InitialValue = '';

% Frame RT_DL1MK3_Measure_Time_3, 9831204 (0x960324)
% Signal crt_PT_960324_Measured_Time_3
crt_PT_960324_Measured_Time_3 = Simulink.Signal;
crt_PT_960324_Measured_Time_3.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_960324_Measured_Time_3.RTWInfo.Alias = '';
crt_PT_960324_Measured_Time_3.Description = ...
  ['Frame: RT_DL1MK3_Measure_Time_3, 9831204 (0x960324).' char(10) ...
   'Signal: Measured_Time_3.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_960324_Measured_Time_3.DataType = 'fixdt(0, 32, 1.0, 0.0)';
crt_PT_960324_Measured_Time_3.Min = 0.0;
crt_PT_960324_Measured_Time_3.Max = 0.0;
crt_PT_960324_Measured_Time_3.DocUnits = '';
crt_PT_960324_Measured_Time_3.Dimensions = 1;
crt_PT_960324_Measured_Time_3.Complexity = 'real';
crt_PT_960324_Measured_Time_3.SampleTime = -1;
crt_PT_960324_Measured_Time_3.SamplingMode = 'Sample based';
crt_PT_960324_Measured_Time_3.InitialValue = '';

% Frame RT_DL1MK3_Measure_Time_2, 9830948 (0x960224)
% Signal crt_PT_960224_Measured_Time_2
crt_PT_960224_Measured_Time_2 = Simulink.Signal;
crt_PT_960224_Measured_Time_2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_960224_Measured_Time_2.RTWInfo.Alias = '';
crt_PT_960224_Measured_Time_2.Description = ...
  ['Frame: RT_DL1MK3_Measure_Time_2, 9830948 (0x960224).' char(10) ...
   'Signal: Measured_Time_2.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_960224_Measured_Time_2.DataType = 'fixdt(0, 32, 1.0, 0.0)';
crt_PT_960224_Measured_Time_2.Min = 0.0;
crt_PT_960224_Measured_Time_2.Max = 0.0;
crt_PT_960224_Measured_Time_2.DocUnits = '';
crt_PT_960224_Measured_Time_2.Dimensions = 1;
crt_PT_960224_Measured_Time_2.Complexity = 'real';
crt_PT_960224_Measured_Time_2.SampleTime = -1;
crt_PT_960224_Measured_Time_2.SamplingMode = 'Sample based';
crt_PT_960224_Measured_Time_2.InitialValue = '';

% Frame RT_DL1MK3_Measure_Time_1, 9830692 (0x960124)
% Signal crt_PT_960124_Measured_Time_1
crt_PT_960124_Measured_Time_1 = Simulink.Signal;
crt_PT_960124_Measured_Time_1.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_960124_Measured_Time_1.RTWInfo.Alias = '';
crt_PT_960124_Measured_Time_1.Description = ...
  ['Frame: RT_DL1MK3_Measure_Time_1, 9830692 (0x960124).' char(10) ...
   'Signal: Measured_Time_1.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_960124_Measured_Time_1.DataType = 'fixdt(0, 32, 1.0, 0.0)';
crt_PT_960124_Measured_Time_1.Min = 0.0;
crt_PT_960124_Measured_Time_1.Max = 0.0;
crt_PT_960124_Measured_Time_1.DocUnits = '';
crt_PT_960124_Measured_Time_1.Dimensions = 1;
crt_PT_960124_Measured_Time_1.Complexity = 'real';
crt_PT_960124_Measured_Time_1.SampleTime = -1;
crt_PT_960124_Measured_Time_1.SamplingMode = 'Sample based';
crt_PT_960124_Measured_Time_1.InitialValue = '';

% Frame RT_DL1MK3_RPM, 9767972 (0x950c24)
% Signal crt_PT_950c24_RPM
crt_PT_950c24_RPM = Simulink.Signal;
crt_PT_950c24_RPM.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_950c24_RPM.RTWInfo.Alias = '';
crt_PT_950c24_RPM.Description = ...
  ['Frame: RT_DL1MK3_RPM, 9767972 (0x950c24).' char(10) ...
   'Signal: RPM.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_950c24_RPM.DataType = 'fixdt(0, 16, 1.0, 0.0)';
crt_PT_950c24_RPM.Min = 0.0;
crt_PT_950c24_RPM.Max = 0.0;
crt_PT_950c24_RPM.DocUnits = '';
crt_PT_950c24_RPM.Dimensions = 1;
crt_PT_950c24_RPM.Complexity = 'real';
crt_PT_950c24_RPM.SampleTime = -1;
crt_PT_950c24_RPM.SamplingMode = 'Sample based';
crt_PT_950c24_RPM.InitialValue = '';

% Frame RT_DL1MK3_Freq_4, 9767716 (0x950b24)
% Signal crt_PT_950b24_Frequency_4
crt_PT_950b24_Frequency_4 = Simulink.Signal;
crt_PT_950b24_Frequency_4.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_950b24_Frequency_4.RTWInfo.Alias = '';
crt_PT_950b24_Frequency_4.Description = ...
  ['Frame: RT_DL1MK3_Freq_4, 9767716 (0x950b24).' char(10) ...
   'Signal: Frequency_4.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_950b24_Frequency_4.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_950b24_Frequency_4.Min = 0.0;
crt_PT_950b24_Frequency_4.Max = 0.0;
crt_PT_950b24_Frequency_4.DocUnits = '';
crt_PT_950b24_Frequency_4.Dimensions = 1;
crt_PT_950b24_Frequency_4.Complexity = 'real';
crt_PT_950b24_Frequency_4.SampleTime = -1;
crt_PT_950b24_Frequency_4.SamplingMode = 'Sample based';
crt_PT_950b24_Frequency_4.InitialValue = '';

% Frame RT_DL1MK3_Freq_3, 9767460 (0x950a24)
% Signal crt_PT_950a24_Frequency_3
crt_PT_950a24_Frequency_3 = Simulink.Signal;
crt_PT_950a24_Frequency_3.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_950a24_Frequency_3.RTWInfo.Alias = '';
crt_PT_950a24_Frequency_3.Description = ...
  ['Frame: RT_DL1MK3_Freq_3, 9767460 (0x950a24).' char(10) ...
   'Signal: Frequency_3.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_950a24_Frequency_3.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_950a24_Frequency_3.Min = 0.0;
crt_PT_950a24_Frequency_3.Max = 0.0;
crt_PT_950a24_Frequency_3.DocUnits = '';
crt_PT_950a24_Frequency_3.Dimensions = 1;
crt_PT_950a24_Frequency_3.Complexity = 'real';
crt_PT_950a24_Frequency_3.SampleTime = -1;
crt_PT_950a24_Frequency_3.SamplingMode = 'Sample based';
crt_PT_950a24_Frequency_3.InitialValue = '';

% Frame RT_DL1MK3_Freq_2, 9767204 (0x950924)
% Signal crt_PT_950924_Frequency_2
crt_PT_950924_Frequency_2 = Simulink.Signal;
crt_PT_950924_Frequency_2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_950924_Frequency_2.RTWInfo.Alias = '';
crt_PT_950924_Frequency_2.Description = ...
  ['Frame: RT_DL1MK3_Freq_2, 9767204 (0x950924).' char(10) ...
   'Signal: Frequency_2.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_950924_Frequency_2.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_950924_Frequency_2.Min = 0.0;
crt_PT_950924_Frequency_2.Max = 0.0;
crt_PT_950924_Frequency_2.DocUnits = '';
crt_PT_950924_Frequency_2.Dimensions = 1;
crt_PT_950924_Frequency_2.Complexity = 'real';
crt_PT_950924_Frequency_2.SampleTime = -1;
crt_PT_950924_Frequency_2.SamplingMode = 'Sample based';
crt_PT_950924_Frequency_2.InitialValue = '';

% Frame RT_DL1MK3_Misc_3, 9896740 (0x970324)
% Signal crt_PT_970324_Misc_3
crt_PT_970324_Misc_3 = Simulink.Signal;
crt_PT_970324_Misc_3.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_970324_Misc_3.RTWInfo.Alias = '';
crt_PT_970324_Misc_3.Description = ...
  ['Frame: RT_DL1MK3_Misc_3, 9896740 (0x970324).' char(10) ...
   'Signal: Misc_3.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_970324_Misc_3.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_970324_Misc_3.Min = 0.0;
crt_PT_970324_Misc_3.Max = 0.0;
crt_PT_970324_Misc_3.DocUnits = '';
crt_PT_970324_Misc_3.Dimensions = 1;
crt_PT_970324_Misc_3.Complexity = 'real';
crt_PT_970324_Misc_3.SampleTime = -1;
crt_PT_970324_Misc_3.SamplingMode = 'Sample based';
crt_PT_970324_Misc_3.InitialValue = '';

% Frame RT_DL1MK3_Misc_2, 9896484 (0x970224)
% Signal crt_PT_970224_Misc_2
crt_PT_970224_Misc_2 = Simulink.Signal;
crt_PT_970224_Misc_2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_970224_Misc_2.RTWInfo.Alias = '';
crt_PT_970224_Misc_2.Description = ...
  ['Frame: RT_DL1MK3_Misc_2, 9896484 (0x970224).' char(10) ...
   'Signal: Misc_2.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_970224_Misc_2.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_970224_Misc_2.Min = 0.0;
crt_PT_970224_Misc_2.Max = 0.0;
crt_PT_970224_Misc_2.DocUnits = '';
crt_PT_970224_Misc_2.Dimensions = 1;
crt_PT_970224_Misc_2.Complexity = 'real';
crt_PT_970224_Misc_2.SampleTime = -1;
crt_PT_970224_Misc_2.SamplingMode = 'Sample based';
crt_PT_970224_Misc_2.InitialValue = '';

% Frame RT_DL1MK3_Misc_1, 9896228 (0x970124)
% Signal crt_PT_970124_Misc_1
crt_PT_970124_Misc_1 = Simulink.Signal;
crt_PT_970124_Misc_1.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_970124_Misc_1.RTWInfo.Alias = '';
crt_PT_970124_Misc_1.Description = ...
  ['Frame: RT_DL1MK3_Misc_1, 9896228 (0x970124).' char(10) ...
   'Signal: Misc_1.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_970124_Misc_1.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_970124_Misc_1.Min = 0.0;
crt_PT_970124_Misc_1.Max = 0.0;
crt_PT_970124_Misc_1.DocUnits = '';
crt_PT_970124_Misc_1.Dimensions = 1;
crt_PT_970124_Misc_1.Complexity = 'real';
crt_PT_970124_Misc_1.SampleTime = -1;
crt_PT_970124_Misc_1.SamplingMode = 'Sample based';
crt_PT_970124_Misc_1.InitialValue = '';

% Frame RT_DL1MK3_Aux_31, 9707300 (0x941f24)
% Signal crt_PT_941f24_AUX_31
crt_PT_941f24_AUX_31 = Simulink.Signal;
crt_PT_941f24_AUX_31.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_941f24_AUX_31.RTWInfo.Alias = '';
crt_PT_941f24_AUX_31.Description = ...
  ['Frame: RT_DL1MK3_Aux_31, 9707300 (0x941f24).' char(10) ...
   'Signal: AUX_31.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_941f24_AUX_31.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_941f24_AUX_31.Min = 0.0;
crt_PT_941f24_AUX_31.Max = 0.0;
crt_PT_941f24_AUX_31.DocUnits = '';
crt_PT_941f24_AUX_31.Dimensions = 1;
crt_PT_941f24_AUX_31.Complexity = 'real';
crt_PT_941f24_AUX_31.SampleTime = -1;
crt_PT_941f24_AUX_31.SamplingMode = 'Sample based';
crt_PT_941f24_AUX_31.InitialValue = '';

% Frame RT_DL1MK3_Aux_30, 9707044 (0x941e24)
% Signal crt_PT_941e24_AUX_30
crt_PT_941e24_AUX_30 = Simulink.Signal;
crt_PT_941e24_AUX_30.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_941e24_AUX_30.RTWInfo.Alias = '';
crt_PT_941e24_AUX_30.Description = ...
  ['Frame: RT_DL1MK3_Aux_30, 9707044 (0x941e24).' char(10) ...
   'Signal: AUX_30.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_941e24_AUX_30.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_941e24_AUX_30.Min = 0.0;
crt_PT_941e24_AUX_30.Max = 0.0;
crt_PT_941e24_AUX_30.DocUnits = '';
crt_PT_941e24_AUX_30.Dimensions = 1;
crt_PT_941e24_AUX_30.Complexity = 'real';
crt_PT_941e24_AUX_30.SampleTime = -1;
crt_PT_941e24_AUX_30.SamplingMode = 'Sample based';
crt_PT_941e24_AUX_30.InitialValue = '';

% Frame RT_DL1MK3_Aux_29, 9706788 (0x941d24)
% Signal crt_PT_941d24_AUX_29
crt_PT_941d24_AUX_29 = Simulink.Signal;
crt_PT_941d24_AUX_29.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_941d24_AUX_29.RTWInfo.Alias = '';
crt_PT_941d24_AUX_29.Description = ...
  ['Frame: RT_DL1MK3_Aux_29, 9706788 (0x941d24).' char(10) ...
   'Signal: AUX_29.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_941d24_AUX_29.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_941d24_AUX_29.Min = 0.0;
crt_PT_941d24_AUX_29.Max = 0.0;
crt_PT_941d24_AUX_29.DocUnits = '';
crt_PT_941d24_AUX_29.Dimensions = 1;
crt_PT_941d24_AUX_29.Complexity = 'real';
crt_PT_941d24_AUX_29.SampleTime = -1;
crt_PT_941d24_AUX_29.SamplingMode = 'Sample based';
crt_PT_941d24_AUX_29.InitialValue = '';

% Frame RT_DL1MK3_Aux_28, 9706532 (0x941c24)
% Signal crt_PT_941c24_AUX_28
crt_PT_941c24_AUX_28 = Simulink.Signal;
crt_PT_941c24_AUX_28.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_941c24_AUX_28.RTWInfo.Alias = '';
crt_PT_941c24_AUX_28.Description = ...
  ['Frame: RT_DL1MK3_Aux_28, 9706532 (0x941c24).' char(10) ...
   'Signal: AUX_28.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_941c24_AUX_28.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_941c24_AUX_28.Min = 0.0;
crt_PT_941c24_AUX_28.Max = 0.0;
crt_PT_941c24_AUX_28.DocUnits = '';
crt_PT_941c24_AUX_28.Dimensions = 1;
crt_PT_941c24_AUX_28.Complexity = 'real';
crt_PT_941c24_AUX_28.SampleTime = -1;
crt_PT_941c24_AUX_28.SamplingMode = 'Sample based';
crt_PT_941c24_AUX_28.InitialValue = '';

% Frame RT_DL1MK3_Aux_27, 9706276 (0x941b24)
% Signal crt_PT_941b24_AUX_27
crt_PT_941b24_AUX_27 = Simulink.Signal;
crt_PT_941b24_AUX_27.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_941b24_AUX_27.RTWInfo.Alias = '';
crt_PT_941b24_AUX_27.Description = ...
  ['Frame: RT_DL1MK3_Aux_27, 9706276 (0x941b24).' char(10) ...
   'Signal: AUX_27.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_941b24_AUX_27.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_941b24_AUX_27.Min = 0.0;
crt_PT_941b24_AUX_27.Max = 0.0;
crt_PT_941b24_AUX_27.DocUnits = '';
crt_PT_941b24_AUX_27.Dimensions = 1;
crt_PT_941b24_AUX_27.Complexity = 'real';
crt_PT_941b24_AUX_27.SampleTime = -1;
crt_PT_941b24_AUX_27.SamplingMode = 'Sample based';
crt_PT_941b24_AUX_27.InitialValue = '';

% Frame RT_DL1MK3_Aux_26, 9706020 (0x941a24)
% Signal crt_PT_941a24_AUX_26
crt_PT_941a24_AUX_26 = Simulink.Signal;
crt_PT_941a24_AUX_26.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_941a24_AUX_26.RTWInfo.Alias = '';
crt_PT_941a24_AUX_26.Description = ...
  ['Frame: RT_DL1MK3_Aux_26, 9706020 (0x941a24).' char(10) ...
   'Signal: AUX_26.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_941a24_AUX_26.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_941a24_AUX_26.Min = 0.0;
crt_PT_941a24_AUX_26.Max = 0.0;
crt_PT_941a24_AUX_26.DocUnits = '';
crt_PT_941a24_AUX_26.Dimensions = 1;
crt_PT_941a24_AUX_26.Complexity = 'real';
crt_PT_941a24_AUX_26.SampleTime = -1;
crt_PT_941a24_AUX_26.SamplingMode = 'Sample based';
crt_PT_941a24_AUX_26.InitialValue = '';

% Frame RT_DL1MK3_Aux_25, 9705764 (0x941924)
% Signal crt_PT_941924_AUX_25
crt_PT_941924_AUX_25 = Simulink.Signal;
crt_PT_941924_AUX_25.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_941924_AUX_25.RTWInfo.Alias = '';
crt_PT_941924_AUX_25.Description = ...
  ['Frame: RT_DL1MK3_Aux_25, 9705764 (0x941924).' char(10) ...
   'Signal: AUX_25.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_941924_AUX_25.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_941924_AUX_25.Min = 0.0;
crt_PT_941924_AUX_25.Max = 0.0;
crt_PT_941924_AUX_25.DocUnits = '';
crt_PT_941924_AUX_25.Dimensions = 1;
crt_PT_941924_AUX_25.Complexity = 'real';
crt_PT_941924_AUX_25.SampleTime = -1;
crt_PT_941924_AUX_25.SamplingMode = 'Sample based';
crt_PT_941924_AUX_25.InitialValue = '';

% Frame RT_DL1MK3_Aux_24, 9705508 (0x941824)
% Signal crt_PT_941824_AUX_24
crt_PT_941824_AUX_24 = Simulink.Signal;
crt_PT_941824_AUX_24.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_941824_AUX_24.RTWInfo.Alias = '';
crt_PT_941824_AUX_24.Description = ...
  ['Frame: RT_DL1MK3_Aux_24, 9705508 (0x941824).' char(10) ...
   'Signal: AUX_24.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_941824_AUX_24.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_941824_AUX_24.Min = 0.0;
crt_PT_941824_AUX_24.Max = 0.0;
crt_PT_941824_AUX_24.DocUnits = '';
crt_PT_941824_AUX_24.Dimensions = 1;
crt_PT_941824_AUX_24.Complexity = 'real';
crt_PT_941824_AUX_24.SampleTime = -1;
crt_PT_941824_AUX_24.SamplingMode = 'Sample based';
crt_PT_941824_AUX_24.InitialValue = '';

% Frame RT_DL1MK3_Aux_23, 9705252 (0x941724)
% Signal crt_PT_941724_AUX_23
crt_PT_941724_AUX_23 = Simulink.Signal;
crt_PT_941724_AUX_23.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_941724_AUX_23.RTWInfo.Alias = '';
crt_PT_941724_AUX_23.Description = ...
  ['Frame: RT_DL1MK3_Aux_23, 9705252 (0x941724).' char(10) ...
   'Signal: AUX_23.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_941724_AUX_23.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_941724_AUX_23.Min = 0.0;
crt_PT_941724_AUX_23.Max = 0.0;
crt_PT_941724_AUX_23.DocUnits = '';
crt_PT_941724_AUX_23.Dimensions = 1;
crt_PT_941724_AUX_23.Complexity = 'real';
crt_PT_941724_AUX_23.SampleTime = -1;
crt_PT_941724_AUX_23.SamplingMode = 'Sample based';
crt_PT_941724_AUX_23.InitialValue = '';

% Frame RT_DL1MK3_Aux_22, 9704996 (0x941624)
% Signal crt_PT_941624_AUX_22
crt_PT_941624_AUX_22 = Simulink.Signal;
crt_PT_941624_AUX_22.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_941624_AUX_22.RTWInfo.Alias = '';
crt_PT_941624_AUX_22.Description = ...
  ['Frame: RT_DL1MK3_Aux_22, 9704996 (0x941624).' char(10) ...
   'Signal: AUX_22.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 10.0*BinaryValue + 0.0 []' ...
  ];
crt_PT_941624_AUX_22.DataType = 'fixdt(0, 16, 10.0, 0.0)';
crt_PT_941624_AUX_22.Min = 0.0;
crt_PT_941624_AUX_22.Max = 0.0;
crt_PT_941624_AUX_22.DocUnits = '';
crt_PT_941624_AUX_22.Dimensions = 1;
crt_PT_941624_AUX_22.Complexity = 'real';
crt_PT_941624_AUX_22.SampleTime = -1;
crt_PT_941624_AUX_22.SamplingMode = 'Sample based';
crt_PT_941624_AUX_22.InitialValue = '';

% Frame RT_DL1MK3_Aux_21, 9704740 (0x941524)
% Signal crt_PT_941524_AUX_21
crt_PT_941524_AUX_21 = Simulink.Signal;
crt_PT_941524_AUX_21.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_941524_AUX_21.RTWInfo.Alias = '';
crt_PT_941524_AUX_21.Description = ...
  ['Frame: RT_DL1MK3_Aux_21, 9704740 (0x941524).' char(10) ...
   'Signal: AUX_21.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_941524_AUX_21.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_941524_AUX_21.Min = 0.0;
crt_PT_941524_AUX_21.Max = 0.0;
crt_PT_941524_AUX_21.DocUnits = '';
crt_PT_941524_AUX_21.Dimensions = 1;
crt_PT_941524_AUX_21.Complexity = 'real';
crt_PT_941524_AUX_21.SampleTime = -1;
crt_PT_941524_AUX_21.SamplingMode = 'Sample based';
crt_PT_941524_AUX_21.InitialValue = '';

% Frame RT_DL1MK3_Aux_20, 9704484 (0x941424)
% Signal crt_PT_941424_AUX_20
crt_PT_941424_AUX_20 = Simulink.Signal;
crt_PT_941424_AUX_20.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_941424_AUX_20.RTWInfo.Alias = '';
crt_PT_941424_AUX_20.Description = ...
  ['Frame: RT_DL1MK3_Aux_20, 9704484 (0x941424).' char(10) ...
   'Signal: AUX_20.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_941424_AUX_20.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_941424_AUX_20.Min = 0.0;
crt_PT_941424_AUX_20.Max = 0.0;
crt_PT_941424_AUX_20.DocUnits = '';
crt_PT_941424_AUX_20.Dimensions = 1;
crt_PT_941424_AUX_20.Complexity = 'real';
crt_PT_941424_AUX_20.SampleTime = -1;
crt_PT_941424_AUX_20.SamplingMode = 'Sample based';
crt_PT_941424_AUX_20.InitialValue = '';

% Frame RT_DL1MK3_Aux_19, 9704228 (0x941324)
% Signal crt_PT_941324_AUX_19
crt_PT_941324_AUX_19 = Simulink.Signal;
crt_PT_941324_AUX_19.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_941324_AUX_19.RTWInfo.Alias = '';
crt_PT_941324_AUX_19.Description = ...
  ['Frame: RT_DL1MK3_Aux_19, 9704228 (0x941324).' char(10) ...
   'Signal: AUX_19.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_941324_AUX_19.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_941324_AUX_19.Min = 0.0;
crt_PT_941324_AUX_19.Max = 0.0;
crt_PT_941324_AUX_19.DocUnits = '';
crt_PT_941324_AUX_19.Dimensions = 1;
crt_PT_941324_AUX_19.Complexity = 'real';
crt_PT_941324_AUX_19.SampleTime = -1;
crt_PT_941324_AUX_19.SamplingMode = 'Sample based';
crt_PT_941324_AUX_19.InitialValue = '';

% Frame RT_DL1MK3_Aux_18, 9703972 (0x941224)
% Signal crt_PT_941224_AUX_18
crt_PT_941224_AUX_18 = Simulink.Signal;
crt_PT_941224_AUX_18.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_941224_AUX_18.RTWInfo.Alias = '';
crt_PT_941224_AUX_18.Description = ...
  ['Frame: RT_DL1MK3_Aux_18, 9703972 (0x941224).' char(10) ...
   'Signal: AUX_18.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_941224_AUX_18.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_941224_AUX_18.Min = 0.0;
crt_PT_941224_AUX_18.Max = 0.0;
crt_PT_941224_AUX_18.DocUnits = '';
crt_PT_941224_AUX_18.Dimensions = 1;
crt_PT_941224_AUX_18.Complexity = 'real';
crt_PT_941224_AUX_18.SampleTime = -1;
crt_PT_941224_AUX_18.SamplingMode = 'Sample based';
crt_PT_941224_AUX_18.InitialValue = '';

% Frame RT_DL1MK3_Aux_17, 9703716 (0x941124)
% Signal crt_PT_941124_AUX_17
crt_PT_941124_AUX_17 = Simulink.Signal;
crt_PT_941124_AUX_17.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_941124_AUX_17.RTWInfo.Alias = '';
crt_PT_941124_AUX_17.Description = ...
  ['Frame: RT_DL1MK3_Aux_17, 9703716 (0x941124).' char(10) ...
   'Signal: AUX_17.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_941124_AUX_17.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_941124_AUX_17.Min = 0.0;
crt_PT_941124_AUX_17.Max = 0.0;
crt_PT_941124_AUX_17.DocUnits = '';
crt_PT_941124_AUX_17.Dimensions = 1;
crt_PT_941124_AUX_17.Complexity = 'real';
crt_PT_941124_AUX_17.SampleTime = -1;
crt_PT_941124_AUX_17.SamplingMode = 'Sample based';
crt_PT_941124_AUX_17.InitialValue = '';

% Frame RT_DL1MK3_Aux_16, 9703460 (0x941024)
% Signal crt_PT_941024_AUX_16
crt_PT_941024_AUX_16 = Simulink.Signal;
crt_PT_941024_AUX_16.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_941024_AUX_16.RTWInfo.Alias = '';
crt_PT_941024_AUX_16.Description = ...
  ['Frame: RT_DL1MK3_Aux_16, 9703460 (0x941024).' char(10) ...
   'Signal: AUX_16.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_941024_AUX_16.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_941024_AUX_16.Min = 0.0;
crt_PT_941024_AUX_16.Max = 0.0;
crt_PT_941024_AUX_16.DocUnits = '';
crt_PT_941024_AUX_16.Dimensions = 1;
crt_PT_941024_AUX_16.Complexity = 'real';
crt_PT_941024_AUX_16.SampleTime = -1;
crt_PT_941024_AUX_16.SamplingMode = 'Sample based';
crt_PT_941024_AUX_16.InitialValue = '';

% Frame RT_DL1MK3_Aux_15, 9703204 (0x940f24)
% Signal crt_PT_940f24_AUX_15
crt_PT_940f24_AUX_15 = Simulink.Signal;
crt_PT_940f24_AUX_15.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_940f24_AUX_15.RTWInfo.Alias = '';
crt_PT_940f24_AUX_15.Description = ...
  ['Frame: RT_DL1MK3_Aux_15, 9703204 (0x940f24).' char(10) ...
   'Signal: AUX_15.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_940f24_AUX_15.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_940f24_AUX_15.Min = 0.0;
crt_PT_940f24_AUX_15.Max = 0.0;
crt_PT_940f24_AUX_15.DocUnits = '';
crt_PT_940f24_AUX_15.Dimensions = 1;
crt_PT_940f24_AUX_15.Complexity = 'real';
crt_PT_940f24_AUX_15.SampleTime = -1;
crt_PT_940f24_AUX_15.SamplingMode = 'Sample based';
crt_PT_940f24_AUX_15.InitialValue = '';

% Frame RT_DL1MK3_Aux_14, 9702948 (0x940e24)
% Signal crt_PT_940e24_AUX_14
crt_PT_940e24_AUX_14 = Simulink.Signal;
crt_PT_940e24_AUX_14.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_940e24_AUX_14.RTWInfo.Alias = '';
crt_PT_940e24_AUX_14.Description = ...
  ['Frame: RT_DL1MK3_Aux_14, 9702948 (0x940e24).' char(10) ...
   'Signal: AUX_14.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_940e24_AUX_14.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_940e24_AUX_14.Min = 0.0;
crt_PT_940e24_AUX_14.Max = 0.0;
crt_PT_940e24_AUX_14.DocUnits = '';
crt_PT_940e24_AUX_14.Dimensions = 1;
crt_PT_940e24_AUX_14.Complexity = 'real';
crt_PT_940e24_AUX_14.SampleTime = -1;
crt_PT_940e24_AUX_14.SamplingMode = 'Sample based';
crt_PT_940e24_AUX_14.InitialValue = '';

% Frame RT_DL1MK3_Aux_13, 9702692 (0x940d24)
% Signal crt_PT_940d24_AUX_13
crt_PT_940d24_AUX_13 = Simulink.Signal;
crt_PT_940d24_AUX_13.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_940d24_AUX_13.RTWInfo.Alias = '';
crt_PT_940d24_AUX_13.Description = ...
  ['Frame: RT_DL1MK3_Aux_13, 9702692 (0x940d24).' char(10) ...
   'Signal: AUX_13.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_940d24_AUX_13.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_940d24_AUX_13.Min = 0.0;
crt_PT_940d24_AUX_13.Max = 0.0;
crt_PT_940d24_AUX_13.DocUnits = '';
crt_PT_940d24_AUX_13.Dimensions = 1;
crt_PT_940d24_AUX_13.Complexity = 'real';
crt_PT_940d24_AUX_13.SampleTime = -1;
crt_PT_940d24_AUX_13.SamplingMode = 'Sample based';
crt_PT_940d24_AUX_13.InitialValue = '';

% Frame RT_DL1MK3_Aux_12, 9702436 (0x940c24)
% Signal crt_PT_940c24_AUX_12
crt_PT_940c24_AUX_12 = Simulink.Signal;
crt_PT_940c24_AUX_12.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_940c24_AUX_12.RTWInfo.Alias = '';
crt_PT_940c24_AUX_12.Description = ...
  ['Frame: RT_DL1MK3_Aux_12, 9702436 (0x940c24).' char(10) ...
   'Signal: AUX_12.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_940c24_AUX_12.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_940c24_AUX_12.Min = 0.0;
crt_PT_940c24_AUX_12.Max = 0.0;
crt_PT_940c24_AUX_12.DocUnits = '';
crt_PT_940c24_AUX_12.Dimensions = 1;
crt_PT_940c24_AUX_12.Complexity = 'real';
crt_PT_940c24_AUX_12.SampleTime = -1;
crt_PT_940c24_AUX_12.SamplingMode = 'Sample based';
crt_PT_940c24_AUX_12.InitialValue = '';

% Frame RT_DL1MK3_Aux_11, 9702180 (0x940b24)
% Signal crt_PT_940b24_AUX_11
crt_PT_940b24_AUX_11 = Simulink.Signal;
crt_PT_940b24_AUX_11.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_940b24_AUX_11.RTWInfo.Alias = '';
crt_PT_940b24_AUX_11.Description = ...
  ['Frame: RT_DL1MK3_Aux_11, 9702180 (0x940b24).' char(10) ...
   'Signal: AUX_11.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_940b24_AUX_11.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_940b24_AUX_11.Min = 0.0;
crt_PT_940b24_AUX_11.Max = 0.0;
crt_PT_940b24_AUX_11.DocUnits = '';
crt_PT_940b24_AUX_11.Dimensions = 1;
crt_PT_940b24_AUX_11.Complexity = 'real';
crt_PT_940b24_AUX_11.SampleTime = -1;
crt_PT_940b24_AUX_11.SamplingMode = 'Sample based';
crt_PT_940b24_AUX_11.InitialValue = '';

% Frame RT_DL1MK3_Aux_9, 9701668 (0x940924)
% Signal crt_PT_940924_AUX_9
crt_PT_940924_AUX_9 = Simulink.Signal;
crt_PT_940924_AUX_9.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_940924_AUX_9.RTWInfo.Alias = '';
crt_PT_940924_AUX_9.Description = ...
  ['Frame: RT_DL1MK3_Aux_9, 9701668 (0x940924).' char(10) ...
   'Signal: AUX_9.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_940924_AUX_9.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_940924_AUX_9.Min = 0.0;
crt_PT_940924_AUX_9.Max = 0.0;
crt_PT_940924_AUX_9.DocUnits = '';
crt_PT_940924_AUX_9.Dimensions = 1;
crt_PT_940924_AUX_9.Complexity = 'real';
crt_PT_940924_AUX_9.SampleTime = -1;
crt_PT_940924_AUX_9.SamplingMode = 'Sample based';
crt_PT_940924_AUX_9.InitialValue = '';

% Frame RT_DL1MK3_Aux_10, 9701924 (0x940a24)
% Signal crt_PT_940a24_AUX_10
crt_PT_940a24_AUX_10 = Simulink.Signal;
crt_PT_940a24_AUX_10.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_940a24_AUX_10.RTWInfo.Alias = '';
crt_PT_940a24_AUX_10.Description = ...
  ['Frame: RT_DL1MK3_Aux_10, 9701924 (0x940a24).' char(10) ...
   'Signal: AUX_10.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_940a24_AUX_10.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_940a24_AUX_10.Min = 0.0;
crt_PT_940a24_AUX_10.Max = 0.0;
crt_PT_940a24_AUX_10.DocUnits = '';
crt_PT_940a24_AUX_10.Dimensions = 1;
crt_PT_940a24_AUX_10.Complexity = 'real';
crt_PT_940a24_AUX_10.SampleTime = -1;
crt_PT_940a24_AUX_10.SamplingMode = 'Sample based';
crt_PT_940a24_AUX_10.InitialValue = '';

% Frame RT_DL1MK3_Aux_8, 9701412 (0x940824)
% Signal crt_PT_940824_AUX_8
crt_PT_940824_AUX_8 = Simulink.Signal;
crt_PT_940824_AUX_8.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_940824_AUX_8.RTWInfo.Alias = '';
crt_PT_940824_AUX_8.Description = ...
  ['Frame: RT_DL1MK3_Aux_8, 9701412 (0x940824).' char(10) ...
   'Signal: AUX_8.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_940824_AUX_8.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_940824_AUX_8.Min = 0.0;
crt_PT_940824_AUX_8.Max = 0.0;
crt_PT_940824_AUX_8.DocUnits = '';
crt_PT_940824_AUX_8.Dimensions = 1;
crt_PT_940824_AUX_8.Complexity = 'real';
crt_PT_940824_AUX_8.SampleTime = -1;
crt_PT_940824_AUX_8.SamplingMode = 'Sample based';
crt_PT_940824_AUX_8.InitialValue = '';

% Frame RT_DL1MK3_Aux_7, 9701156 (0x940724)
% Signal crt_PT_940724_AUX_7
crt_PT_940724_AUX_7 = Simulink.Signal;
crt_PT_940724_AUX_7.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_940724_AUX_7.RTWInfo.Alias = '';
crt_PT_940724_AUX_7.Description = ...
  ['Frame: RT_DL1MK3_Aux_7, 9701156 (0x940724).' char(10) ...
   'Signal: AUX_7.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_940724_AUX_7.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_940724_AUX_7.Min = 0.0;
crt_PT_940724_AUX_7.Max = 0.0;
crt_PT_940724_AUX_7.DocUnits = '';
crt_PT_940724_AUX_7.Dimensions = 1;
crt_PT_940724_AUX_7.Complexity = 'real';
crt_PT_940724_AUX_7.SampleTime = -1;
crt_PT_940724_AUX_7.SamplingMode = 'Sample based';
crt_PT_940724_AUX_7.InitialValue = '';

% Frame RT_DL1MK3_Aux_6, 9700900 (0x940624)
% Signal crt_PT_940624_AUX_6
crt_PT_940624_AUX_6 = Simulink.Signal;
crt_PT_940624_AUX_6.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_940624_AUX_6.RTWInfo.Alias = '';
crt_PT_940624_AUX_6.Description = ...
  ['Frame: RT_DL1MK3_Aux_6, 9700900 (0x940624).' char(10) ...
   'Signal: AUX_6.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_940624_AUX_6.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_940624_AUX_6.Min = 0.0;
crt_PT_940624_AUX_6.Max = 0.0;
crt_PT_940624_AUX_6.DocUnits = '';
crt_PT_940624_AUX_6.Dimensions = 1;
crt_PT_940624_AUX_6.Complexity = 'real';
crt_PT_940624_AUX_6.SampleTime = -1;
crt_PT_940624_AUX_6.SamplingMode = 'Sample based';
crt_PT_940624_AUX_6.InitialValue = '';

% Frame RT_DL1MK3_Aux_5, 9700644 (0x940524)
% Signal crt_PT_940524_AUX_5
crt_PT_940524_AUX_5 = Simulink.Signal;
crt_PT_940524_AUX_5.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_940524_AUX_5.RTWInfo.Alias = '';
crt_PT_940524_AUX_5.Description = ...
  ['Frame: RT_DL1MK3_Aux_5, 9700644 (0x940524).' char(10) ...
   'Signal: AUX_5.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_940524_AUX_5.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_940524_AUX_5.Min = 0.0;
crt_PT_940524_AUX_5.Max = 0.0;
crt_PT_940524_AUX_5.DocUnits = '';
crt_PT_940524_AUX_5.Dimensions = 1;
crt_PT_940524_AUX_5.Complexity = 'real';
crt_PT_940524_AUX_5.SampleTime = -1;
crt_PT_940524_AUX_5.SamplingMode = 'Sample based';
crt_PT_940524_AUX_5.InitialValue = '';

% Frame RT_DL1MK3_Aux_4, 9700388 (0x940424)
% Signal crt_PT_940424_AUX_4
crt_PT_940424_AUX_4 = Simulink.Signal;
crt_PT_940424_AUX_4.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_940424_AUX_4.RTWInfo.Alias = '';
crt_PT_940424_AUX_4.Description = ...
  ['Frame: RT_DL1MK3_Aux_4, 9700388 (0x940424).' char(10) ...
   'Signal: AUX_4.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_940424_AUX_4.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_940424_AUX_4.Min = 0.0;
crt_PT_940424_AUX_4.Max = 0.0;
crt_PT_940424_AUX_4.DocUnits = '';
crt_PT_940424_AUX_4.Dimensions = 1;
crt_PT_940424_AUX_4.Complexity = 'real';
crt_PT_940424_AUX_4.SampleTime = -1;
crt_PT_940424_AUX_4.SamplingMode = 'Sample based';
crt_PT_940424_AUX_4.InitialValue = '';

% Frame RT_DL1MK3_Aux_3, 9700132 (0x940324)
% Signal crt_PT_940324_AUX_3
crt_PT_940324_AUX_3 = Simulink.Signal;
crt_PT_940324_AUX_3.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_940324_AUX_3.RTWInfo.Alias = '';
crt_PT_940324_AUX_3.Description = ...
  ['Frame: RT_DL1MK3_Aux_3, 9700132 (0x940324).' char(10) ...
   'Signal: AUX_3.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_940324_AUX_3.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_940324_AUX_3.Min = 0.0;
crt_PT_940324_AUX_3.Max = 0.0;
crt_PT_940324_AUX_3.DocUnits = '';
crt_PT_940324_AUX_3.Dimensions = 1;
crt_PT_940324_AUX_3.Complexity = 'real';
crt_PT_940324_AUX_3.SampleTime = -1;
crt_PT_940324_AUX_3.SamplingMode = 'Sample based';
crt_PT_940324_AUX_3.InitialValue = '';

% Frame RT_DL1MK3_Aux_2, 9699876 (0x940224)
% Signal crt_PT_940224_AUX_2
crt_PT_940224_AUX_2 = Simulink.Signal;
crt_PT_940224_AUX_2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_940224_AUX_2.RTWInfo.Alias = '';
crt_PT_940224_AUX_2.Description = ...
  ['Frame: RT_DL1MK3_Aux_2, 9699876 (0x940224).' char(10) ...
   'Signal: AUX_2.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_940224_AUX_2.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_940224_AUX_2.Min = 0.0;
crt_PT_940224_AUX_2.Max = 0.0;
crt_PT_940224_AUX_2.DocUnits = '';
crt_PT_940224_AUX_2.Dimensions = 1;
crt_PT_940224_AUX_2.Complexity = 'real';
crt_PT_940224_AUX_2.SampleTime = -1;
crt_PT_940224_AUX_2.SamplingMode = 'Sample based';
crt_PT_940224_AUX_2.InitialValue = '';

% Frame RT_DL1MK3_Aux_1, 9699620 (0x940124)
% Signal crt_PT_940124_AUX_1
crt_PT_940124_AUX_1 = Simulink.Signal;
crt_PT_940124_AUX_1.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_940124_AUX_1.RTWInfo.Alias = '';
crt_PT_940124_AUX_1.Description = ...
  ['Frame: RT_DL1MK3_Aux_1, 9699620 (0x940124).' char(10) ...
   'Signal: AUX_1.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_940124_AUX_1.DataType = 'fixdt(0, 16, 0.1, 0.0)';
crt_PT_940124_AUX_1.Min = 0.0;
crt_PT_940124_AUX_1.Max = 0.0;
crt_PT_940124_AUX_1.DocUnits = '';
crt_PT_940124_AUX_1.Dimensions = 1;
crt_PT_940124_AUX_1.Complexity = 'real';
crt_PT_940124_AUX_1.SampleTime = -1;
crt_PT_940124_AUX_1.SamplingMode = 'Sample based';
crt_PT_940124_AUX_1.InitialValue = '';

% Frame RT_DL1MK3_Pressure_5, 9438500 (0x900524)
% Signal crt_PT_900524_Pressure_5
crt_PT_900524_Pressure_5 = Simulink.Signal;
crt_PT_900524_Pressure_5.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_900524_Pressure_5.RTWInfo.Alias = '';
crt_PT_900524_Pressure_5.Description = ...
  ['Frame: RT_DL1MK3_Pressure_5, 9438500 (0x900524).' char(10) ...
   'Signal: Pressure_5.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_900524_Pressure_5.DataType = 'fixdt(0, 32, 0.1, 0.0)';
crt_PT_900524_Pressure_5.Min = 0.0;
crt_PT_900524_Pressure_5.Max = 0.0;
crt_PT_900524_Pressure_5.DocUnits = '';
crt_PT_900524_Pressure_5.Dimensions = 1;
crt_PT_900524_Pressure_5.Complexity = 'real';
crt_PT_900524_Pressure_5.SampleTime = -1;
crt_PT_900524_Pressure_5.SamplingMode = 'Sample based';
crt_PT_900524_Pressure_5.InitialValue = '';

% Frame RT_DL1MK3_Pressure_4, 9438244 (0x900424)
% Signal crt_PT_900424_Pressure_4
crt_PT_900424_Pressure_4 = Simulink.Signal;
crt_PT_900424_Pressure_4.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_900424_Pressure_4.RTWInfo.Alias = '';
crt_PT_900424_Pressure_4.Description = ...
  ['Frame: RT_DL1MK3_Pressure_4, 9438244 (0x900424).' char(10) ...
   'Signal: Pressure_4.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_900424_Pressure_4.DataType = 'fixdt(0, 32, 0.1, 0.0)';
crt_PT_900424_Pressure_4.Min = 0.0;
crt_PT_900424_Pressure_4.Max = 0.0;
crt_PT_900424_Pressure_4.DocUnits = '';
crt_PT_900424_Pressure_4.Dimensions = 1;
crt_PT_900424_Pressure_4.Complexity = 'real';
crt_PT_900424_Pressure_4.SampleTime = -1;
crt_PT_900424_Pressure_4.SamplingMode = 'Sample based';
crt_PT_900424_Pressure_4.InitialValue = '';

% Frame RT_DL1MK3_Pressure_3, 9437988 (0x900324)
% Signal crt_PT_900324_Pressure_3
crt_PT_900324_Pressure_3 = Simulink.Signal;
crt_PT_900324_Pressure_3.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_900324_Pressure_3.RTWInfo.Alias = '';
crt_PT_900324_Pressure_3.Description = ...
  ['Frame: RT_DL1MK3_Pressure_3, 9437988 (0x900324).' char(10) ...
   'Signal: Pressure_3.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_900324_Pressure_3.DataType = 'fixdt(0, 32, 0.1, 0.0)';
crt_PT_900324_Pressure_3.Min = 0.0;
crt_PT_900324_Pressure_3.Max = 0.0;
crt_PT_900324_Pressure_3.DocUnits = '';
crt_PT_900324_Pressure_3.Dimensions = 1;
crt_PT_900324_Pressure_3.Complexity = 'real';
crt_PT_900324_Pressure_3.SampleTime = -1;
crt_PT_900324_Pressure_3.SamplingMode = 'Sample based';
crt_PT_900324_Pressure_3.InitialValue = '';

% Frame RT_DL1MK3_Pressure_2, 9437732 (0x900224)
% Signal crt_PT_900224_Pressure_2
crt_PT_900224_Pressure_2 = Simulink.Signal;
crt_PT_900224_Pressure_2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_900224_Pressure_2.RTWInfo.Alias = '';
crt_PT_900224_Pressure_2.Description = ...
  ['Frame: RT_DL1MK3_Pressure_2, 9437732 (0x900224).' char(10) ...
   'Signal: Pressure_2.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_900224_Pressure_2.DataType = 'fixdt(0, 32, 0.1, 0.0)';
crt_PT_900224_Pressure_2.Min = 0.0;
crt_PT_900224_Pressure_2.Max = 0.0;
crt_PT_900224_Pressure_2.DocUnits = '';
crt_PT_900224_Pressure_2.Dimensions = 1;
crt_PT_900224_Pressure_2.Complexity = 'real';
crt_PT_900224_Pressure_2.SampleTime = -1;
crt_PT_900224_Pressure_2.SamplingMode = 'Sample based';
crt_PT_900224_Pressure_2.InitialValue = '';

% Frame RT_DL1MK3_Pressure_1, 9437476 (0x900124)
% Signal crt_PT_900124_Pressure_1
crt_PT_900124_Pressure_1 = Simulink.Signal;
crt_PT_900124_Pressure_1.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_900124_Pressure_1.RTWInfo.Alias = '';
crt_PT_900124_Pressure_1.Description = ...
  ['Frame: RT_DL1MK3_Pressure_1, 9437476 (0x900124).' char(10) ...
   'Signal: Pressure_1.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_900124_Pressure_1.DataType = 'fixdt(0, 32, 0.1, 0.0)';
crt_PT_900124_Pressure_1.Min = 0.0;
crt_PT_900124_Pressure_1.Max = 0.0;
crt_PT_900124_Pressure_1.DocUnits = '';
crt_PT_900124_Pressure_1.Dimensions = 1;
crt_PT_900124_Pressure_1.Complexity = 'real';
crt_PT_900124_Pressure_1.SampleTime = -1;
crt_PT_900124_Pressure_1.SamplingMode = 'Sample based';
crt_PT_900124_Pressure_1.InitialValue = '';

% Frame RT_DL1MK3_Angle_3, 9569060 (0x920324)
% Signal crt_PT_920324_Angle_3
crt_PT_920324_Angle_3 = Simulink.Signal;
crt_PT_920324_Angle_3.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_920324_Angle_3.RTWInfo.Alias = '';
crt_PT_920324_Angle_3.Description = ...
  ['Frame: RT_DL1MK3_Angle_3, 9569060 (0x920324).' char(10) ...
   'Signal: Angle_3.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_920324_Angle_3.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_920324_Angle_3.Min = 0.0;
crt_PT_920324_Angle_3.Max = 0.0;
crt_PT_920324_Angle_3.DocUnits = '';
crt_PT_920324_Angle_3.Dimensions = 1;
crt_PT_920324_Angle_3.Complexity = 'real';
crt_PT_920324_Angle_3.SampleTime = -1;
crt_PT_920324_Angle_3.SamplingMode = 'Sample based';
crt_PT_920324_Angle_3.InitialValue = '';

% Frame RT_DL1MK3_Angle_2, 9568804 (0x920224)
% Signal crt_PT_920224_Angle_2
crt_PT_920224_Angle_2 = Simulink.Signal;
crt_PT_920224_Angle_2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_920224_Angle_2.RTWInfo.Alias = '';
crt_PT_920224_Angle_2.Description = ...
  ['Frame: RT_DL1MK3_Angle_2, 9568804 (0x920224).' char(10) ...
   'Signal: Angle_2.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_920224_Angle_2.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_920224_Angle_2.Min = 0.0;
crt_PT_920224_Angle_2.Max = 0.0;
crt_PT_920224_Angle_2.DocUnits = '';
crt_PT_920224_Angle_2.Dimensions = 1;
crt_PT_920224_Angle_2.Complexity = 'real';
crt_PT_920224_Angle_2.SampleTime = -1;
crt_PT_920224_Angle_2.SamplingMode = 'Sample based';
crt_PT_920224_Angle_2.InitialValue = '';

% Frame RT_DL1MK3_Angle_1, 9568548 (0x920124)
% Signal crt_PT_920124_Angle_1
crt_PT_920124_Angle_1 = Simulink.Signal;
crt_PT_920124_Angle_1.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_920124_Angle_1.RTWInfo.Alias = '';
crt_PT_920124_Angle_1.Description = ...
  ['Frame: RT_DL1MK3_Angle_1, 9568548 (0x920124).' char(10) ...
   'Signal: Angle_1.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_920124_Angle_1.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_920124_Angle_1.Min = 0.0;
crt_PT_920124_Angle_1.Max = 0.0;
crt_PT_920124_Angle_1.DocUnits = '';
crt_PT_920124_Angle_1.Dimensions = 1;
crt_PT_920124_Angle_1.Complexity = 'real';
crt_PT_920124_Angle_1.SampleTime = -1;
crt_PT_920124_Angle_1.SamplingMode = 'Sample based';
crt_PT_920124_Angle_1.InitialValue = '';

% Frame RT_DL1MK3_Temp_25, 9509156 (0x911924)
% Signal crt_PT_911924_Temperature_25
crt_PT_911924_Temperature_25 = Simulink.Signal;
crt_PT_911924_Temperature_25.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911924_Temperature_25.RTWInfo.Alias = '';
crt_PT_911924_Temperature_25.Description = ...
  ['Frame: RT_DL1MK3_Temp_25, 9509156 (0x911924).' char(10) ...
   'Signal: Temperature_25.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911924_Temperature_25.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911924_Temperature_25.Min = 0.0;
crt_PT_911924_Temperature_25.Max = 0.0;
crt_PT_911924_Temperature_25.DocUnits = '';
crt_PT_911924_Temperature_25.Dimensions = 1;
crt_PT_911924_Temperature_25.Complexity = 'real';
crt_PT_911924_Temperature_25.SampleTime = -1;
crt_PT_911924_Temperature_25.SamplingMode = 'Sample based';
crt_PT_911924_Temperature_25.InitialValue = '';

% Frame RT_DL1MK3_Temp_24, 9508900 (0x911824)
% Signal crt_PT_911824_Temperature_24
crt_PT_911824_Temperature_24 = Simulink.Signal;
crt_PT_911824_Temperature_24.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911824_Temperature_24.RTWInfo.Alias = '';
crt_PT_911824_Temperature_24.Description = ...
  ['Frame: RT_DL1MK3_Temp_24, 9508900 (0x911824).' char(10) ...
   'Signal: Temperature_24.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911824_Temperature_24.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911824_Temperature_24.Min = 0.0;
crt_PT_911824_Temperature_24.Max = 0.0;
crt_PT_911824_Temperature_24.DocUnits = '';
crt_PT_911824_Temperature_24.Dimensions = 1;
crt_PT_911824_Temperature_24.Complexity = 'real';
crt_PT_911824_Temperature_24.SampleTime = -1;
crt_PT_911824_Temperature_24.SamplingMode = 'Sample based';
crt_PT_911824_Temperature_24.InitialValue = '';

% Frame RT_DL1MK3_Temp_23, 9508644 (0x911724)
% Signal crt_PT_911724_Temperature_23
crt_PT_911724_Temperature_23 = Simulink.Signal;
crt_PT_911724_Temperature_23.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911724_Temperature_23.RTWInfo.Alias = '';
crt_PT_911724_Temperature_23.Description = ...
  ['Frame: RT_DL1MK3_Temp_23, 9508644 (0x911724).' char(10) ...
   'Signal: Temperature_23.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911724_Temperature_23.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911724_Temperature_23.Min = 0.0;
crt_PT_911724_Temperature_23.Max = 0.0;
crt_PT_911724_Temperature_23.DocUnits = '';
crt_PT_911724_Temperature_23.Dimensions = 1;
crt_PT_911724_Temperature_23.Complexity = 'real';
crt_PT_911724_Temperature_23.SampleTime = -1;
crt_PT_911724_Temperature_23.SamplingMode = 'Sample based';
crt_PT_911724_Temperature_23.InitialValue = '';

% Frame RT_DL1MK3_Temp_22, 9508388 (0x911624)
% Signal crt_PT_911624_Temperature_22
crt_PT_911624_Temperature_22 = Simulink.Signal;
crt_PT_911624_Temperature_22.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911624_Temperature_22.RTWInfo.Alias = '';
crt_PT_911624_Temperature_22.Description = ...
  ['Frame: RT_DL1MK3_Temp_22, 9508388 (0x911624).' char(10) ...
   'Signal: Temperature_22.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911624_Temperature_22.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911624_Temperature_22.Min = 0.0;
crt_PT_911624_Temperature_22.Max = 0.0;
crt_PT_911624_Temperature_22.DocUnits = '';
crt_PT_911624_Temperature_22.Dimensions = 1;
crt_PT_911624_Temperature_22.Complexity = 'real';
crt_PT_911624_Temperature_22.SampleTime = -1;
crt_PT_911624_Temperature_22.SamplingMode = 'Sample based';
crt_PT_911624_Temperature_22.InitialValue = '';

% Frame RT_DL1MK3_Temp_21, 9508132 (0x911524)
% Signal crt_PT_911524_Temperature_21
crt_PT_911524_Temperature_21 = Simulink.Signal;
crt_PT_911524_Temperature_21.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911524_Temperature_21.RTWInfo.Alias = '';
crt_PT_911524_Temperature_21.Description = ...
  ['Frame: RT_DL1MK3_Temp_21, 9508132 (0x911524).' char(10) ...
   'Signal: Temperature_21.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911524_Temperature_21.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911524_Temperature_21.Min = 0.0;
crt_PT_911524_Temperature_21.Max = 0.0;
crt_PT_911524_Temperature_21.DocUnits = '';
crt_PT_911524_Temperature_21.Dimensions = 1;
crt_PT_911524_Temperature_21.Complexity = 'real';
crt_PT_911524_Temperature_21.SampleTime = -1;
crt_PT_911524_Temperature_21.SamplingMode = 'Sample based';
crt_PT_911524_Temperature_21.InitialValue = '';

% Frame RT_DL1MK3_Temp_20, 9507876 (0x911424)
% Signal crt_PT_911424_Temperature_20
crt_PT_911424_Temperature_20 = Simulink.Signal;
crt_PT_911424_Temperature_20.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911424_Temperature_20.RTWInfo.Alias = '';
crt_PT_911424_Temperature_20.Description = ...
  ['Frame: RT_DL1MK3_Temp_20, 9507876 (0x911424).' char(10) ...
   'Signal: Temperature_20.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911424_Temperature_20.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911424_Temperature_20.Min = 0.0;
crt_PT_911424_Temperature_20.Max = 0.0;
crt_PT_911424_Temperature_20.DocUnits = '';
crt_PT_911424_Temperature_20.Dimensions = 1;
crt_PT_911424_Temperature_20.Complexity = 'real';
crt_PT_911424_Temperature_20.SampleTime = -1;
crt_PT_911424_Temperature_20.SamplingMode = 'Sample based';
crt_PT_911424_Temperature_20.InitialValue = '';

% Frame RT_DL1MK3_Temp_19, 9507620 (0x911324)
% Signal crt_PT_911324_Temperature_19
crt_PT_911324_Temperature_19 = Simulink.Signal;
crt_PT_911324_Temperature_19.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911324_Temperature_19.RTWInfo.Alias = '';
crt_PT_911324_Temperature_19.Description = ...
  ['Frame: RT_DL1MK3_Temp_19, 9507620 (0x911324).' char(10) ...
   'Signal: Temperature_19.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911324_Temperature_19.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911324_Temperature_19.Min = 0.0;
crt_PT_911324_Temperature_19.Max = 0.0;
crt_PT_911324_Temperature_19.DocUnits = '';
crt_PT_911324_Temperature_19.Dimensions = 1;
crt_PT_911324_Temperature_19.Complexity = 'real';
crt_PT_911324_Temperature_19.SampleTime = -1;
crt_PT_911324_Temperature_19.SamplingMode = 'Sample based';
crt_PT_911324_Temperature_19.InitialValue = '';

% Frame RT_DL1MK3_Temp_18, 9507364 (0x911224)
% Signal crt_PT_911224_Temperature_18
crt_PT_911224_Temperature_18 = Simulink.Signal;
crt_PT_911224_Temperature_18.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911224_Temperature_18.RTWInfo.Alias = '';
crt_PT_911224_Temperature_18.Description = ...
  ['Frame: RT_DL1MK3_Temp_18, 9507364 (0x911224).' char(10) ...
   'Signal: Temperature_18.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911224_Temperature_18.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911224_Temperature_18.Min = 0.0;
crt_PT_911224_Temperature_18.Max = 0.0;
crt_PT_911224_Temperature_18.DocUnits = '';
crt_PT_911224_Temperature_18.Dimensions = 1;
crt_PT_911224_Temperature_18.Complexity = 'real';
crt_PT_911224_Temperature_18.SampleTime = -1;
crt_PT_911224_Temperature_18.SamplingMode = 'Sample based';
crt_PT_911224_Temperature_18.InitialValue = '';

% Frame RT_DL1MK3_Temp_17, 9507108 (0x911124)
% Signal crt_PT_911124_Temperature_17
crt_PT_911124_Temperature_17 = Simulink.Signal;
crt_PT_911124_Temperature_17.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911124_Temperature_17.RTWInfo.Alias = '';
crt_PT_911124_Temperature_17.Description = ...
  ['Frame: RT_DL1MK3_Temp_17, 9507108 (0x911124).' char(10) ...
   'Signal: Temperature_17.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911124_Temperature_17.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911124_Temperature_17.Min = 0.0;
crt_PT_911124_Temperature_17.Max = 0.0;
crt_PT_911124_Temperature_17.DocUnits = '';
crt_PT_911124_Temperature_17.Dimensions = 1;
crt_PT_911124_Temperature_17.Complexity = 'real';
crt_PT_911124_Temperature_17.SampleTime = -1;
crt_PT_911124_Temperature_17.SamplingMode = 'Sample based';
crt_PT_911124_Temperature_17.InitialValue = '';

% Frame RT_DL1MK3_Temp_16, 9506852 (0x911024)
% Signal crt_PT_911024_Temperature_16
crt_PT_911024_Temperature_16 = Simulink.Signal;
crt_PT_911024_Temperature_16.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911024_Temperature_16.RTWInfo.Alias = '';
crt_PT_911024_Temperature_16.Description = ...
  ['Frame: RT_DL1MK3_Temp_16, 9506852 (0x911024).' char(10) ...
   'Signal: Temperature_16.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911024_Temperature_16.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911024_Temperature_16.Min = 0.0;
crt_PT_911024_Temperature_16.Max = 0.0;
crt_PT_911024_Temperature_16.DocUnits = '';
crt_PT_911024_Temperature_16.Dimensions = 1;
crt_PT_911024_Temperature_16.Complexity = 'real';
crt_PT_911024_Temperature_16.SampleTime = -1;
crt_PT_911024_Temperature_16.SamplingMode = 'Sample based';
crt_PT_911024_Temperature_16.InitialValue = '';

% Frame RT_DL1MK3_Temp_15, 9506596 (0x910f24)
% Signal crt_PT_910f24_Temperature_15
crt_PT_910f24_Temperature_15 = Simulink.Signal;
crt_PT_910f24_Temperature_15.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910f24_Temperature_15.RTWInfo.Alias = '';
crt_PT_910f24_Temperature_15.Description = ...
  ['Frame: RT_DL1MK3_Temp_15, 9506596 (0x910f24).' char(10) ...
   'Signal: Temperature_15.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910f24_Temperature_15.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910f24_Temperature_15.Min = 0.0;
crt_PT_910f24_Temperature_15.Max = 0.0;
crt_PT_910f24_Temperature_15.DocUnits = '';
crt_PT_910f24_Temperature_15.Dimensions = 1;
crt_PT_910f24_Temperature_15.Complexity = 'real';
crt_PT_910f24_Temperature_15.SampleTime = -1;
crt_PT_910f24_Temperature_15.SamplingMode = 'Sample based';
crt_PT_910f24_Temperature_15.InitialValue = '';

% Frame RT_DL1MK3_Temp_14, 9506340 (0x910e24)
% Signal crt_PT_910e24_Temperature_14
crt_PT_910e24_Temperature_14 = Simulink.Signal;
crt_PT_910e24_Temperature_14.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910e24_Temperature_14.RTWInfo.Alias = '';
crt_PT_910e24_Temperature_14.Description = ...
  ['Frame: RT_DL1MK3_Temp_14, 9506340 (0x910e24).' char(10) ...
   'Signal: Temperature_14.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910e24_Temperature_14.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910e24_Temperature_14.Min = 0.0;
crt_PT_910e24_Temperature_14.Max = 0.0;
crt_PT_910e24_Temperature_14.DocUnits = '';
crt_PT_910e24_Temperature_14.Dimensions = 1;
crt_PT_910e24_Temperature_14.Complexity = 'real';
crt_PT_910e24_Temperature_14.SampleTime = -1;
crt_PT_910e24_Temperature_14.SamplingMode = 'Sample based';
crt_PT_910e24_Temperature_14.InitialValue = '';

% Frame RT_DL1MK3_Temp_13, 9506084 (0x910d24)
% Signal crt_PT_910d24_Temperature_13
crt_PT_910d24_Temperature_13 = Simulink.Signal;
crt_PT_910d24_Temperature_13.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910d24_Temperature_13.RTWInfo.Alias = '';
crt_PT_910d24_Temperature_13.Description = ...
  ['Frame: RT_DL1MK3_Temp_13, 9506084 (0x910d24).' char(10) ...
   'Signal: Temperature_13.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910d24_Temperature_13.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910d24_Temperature_13.Min = 0.0;
crt_PT_910d24_Temperature_13.Max = 0.0;
crt_PT_910d24_Temperature_13.DocUnits = '';
crt_PT_910d24_Temperature_13.Dimensions = 1;
crt_PT_910d24_Temperature_13.Complexity = 'real';
crt_PT_910d24_Temperature_13.SampleTime = -1;
crt_PT_910d24_Temperature_13.SamplingMode = 'Sample based';
crt_PT_910d24_Temperature_13.InitialValue = '';

% Frame RT_DL1MK3_Temp_12, 9505828 (0x910c24)
% Signal crt_PT_910c24_Temperature_12
crt_PT_910c24_Temperature_12 = Simulink.Signal;
crt_PT_910c24_Temperature_12.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910c24_Temperature_12.RTWInfo.Alias = '';
crt_PT_910c24_Temperature_12.Description = ...
  ['Frame: RT_DL1MK3_Temp_12, 9505828 (0x910c24).' char(10) ...
   'Signal: Temperature_12.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910c24_Temperature_12.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910c24_Temperature_12.Min = 0.0;
crt_PT_910c24_Temperature_12.Max = 0.0;
crt_PT_910c24_Temperature_12.DocUnits = '';
crt_PT_910c24_Temperature_12.Dimensions = 1;
crt_PT_910c24_Temperature_12.Complexity = 'real';
crt_PT_910c24_Temperature_12.SampleTime = -1;
crt_PT_910c24_Temperature_12.SamplingMode = 'Sample based';
crt_PT_910c24_Temperature_12.InitialValue = '';

% Frame RT_DL1MK3_Temp_11, 9505572 (0x910b24)
% Signal crt_PT_910b24_Temperature_11
crt_PT_910b24_Temperature_11 = Simulink.Signal;
crt_PT_910b24_Temperature_11.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910b24_Temperature_11.RTWInfo.Alias = '';
crt_PT_910b24_Temperature_11.Description = ...
  ['Frame: RT_DL1MK3_Temp_11, 9505572 (0x910b24).' char(10) ...
   'Signal: Temperature_11.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910b24_Temperature_11.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910b24_Temperature_11.Min = 0.0;
crt_PT_910b24_Temperature_11.Max = 0.0;
crt_PT_910b24_Temperature_11.DocUnits = '';
crt_PT_910b24_Temperature_11.Dimensions = 1;
crt_PT_910b24_Temperature_11.Complexity = 'real';
crt_PT_910b24_Temperature_11.SampleTime = -1;
crt_PT_910b24_Temperature_11.SamplingMode = 'Sample based';
crt_PT_910b24_Temperature_11.InitialValue = '';

% Frame RT_DL1MK3_Temp_10, 9505316 (0x910a24)
% Signal crt_PT_910a24_Temperature_10
crt_PT_910a24_Temperature_10 = Simulink.Signal;
crt_PT_910a24_Temperature_10.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910a24_Temperature_10.RTWInfo.Alias = '';
crt_PT_910a24_Temperature_10.Description = ...
  ['Frame: RT_DL1MK3_Temp_10, 9505316 (0x910a24).' char(10) ...
   'Signal: Temperature_10.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910a24_Temperature_10.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910a24_Temperature_10.Min = 0.0;
crt_PT_910a24_Temperature_10.Max = 0.0;
crt_PT_910a24_Temperature_10.DocUnits = '';
crt_PT_910a24_Temperature_10.Dimensions = 1;
crt_PT_910a24_Temperature_10.Complexity = 'real';
crt_PT_910a24_Temperature_10.SampleTime = -1;
crt_PT_910a24_Temperature_10.SamplingMode = 'Sample based';
crt_PT_910a24_Temperature_10.InitialValue = '';

% Frame RT_DL1MK3_Temp_9, 9505060 (0x910924)
% Signal crt_PT_910924_Temperature_9
crt_PT_910924_Temperature_9 = Simulink.Signal;
crt_PT_910924_Temperature_9.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910924_Temperature_9.RTWInfo.Alias = '';
crt_PT_910924_Temperature_9.Description = ...
  ['Frame: RT_DL1MK3_Temp_9, 9505060 (0x910924).' char(10) ...
   'Signal: Temperature_9.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910924_Temperature_9.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910924_Temperature_9.Min = 0.0;
crt_PT_910924_Temperature_9.Max = 0.0;
crt_PT_910924_Temperature_9.DocUnits = '';
crt_PT_910924_Temperature_9.Dimensions = 1;
crt_PT_910924_Temperature_9.Complexity = 'real';
crt_PT_910924_Temperature_9.SampleTime = -1;
crt_PT_910924_Temperature_9.SamplingMode = 'Sample based';
crt_PT_910924_Temperature_9.InitialValue = '';

% Frame RT_DL1MK3_Temp_8, 9504804 (0x910824)
% Signal crt_PT_910824_Temperature_8
crt_PT_910824_Temperature_8 = Simulink.Signal;
crt_PT_910824_Temperature_8.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910824_Temperature_8.RTWInfo.Alias = '';
crt_PT_910824_Temperature_8.Description = ...
  ['Frame: RT_DL1MK3_Temp_8, 9504804 (0x910824).' char(10) ...
   'Signal: Temperature_8.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910824_Temperature_8.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910824_Temperature_8.Min = 0.0;
crt_PT_910824_Temperature_8.Max = 0.0;
crt_PT_910824_Temperature_8.DocUnits = '';
crt_PT_910824_Temperature_8.Dimensions = 1;
crt_PT_910824_Temperature_8.Complexity = 'real';
crt_PT_910824_Temperature_8.SampleTime = -1;
crt_PT_910824_Temperature_8.SamplingMode = 'Sample based';
crt_PT_910824_Temperature_8.InitialValue = '';

% Frame RT_DL1MK3_Temp_7, 9504548 (0x910724)
% Signal crt_PT_910724_Temperature_7
crt_PT_910724_Temperature_7 = Simulink.Signal;
crt_PT_910724_Temperature_7.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910724_Temperature_7.RTWInfo.Alias = '';
crt_PT_910724_Temperature_7.Description = ...
  ['Frame: RT_DL1MK3_Temp_7, 9504548 (0x910724).' char(10) ...
   'Signal: Temperature_7.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910724_Temperature_7.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910724_Temperature_7.Min = 0.0;
crt_PT_910724_Temperature_7.Max = 0.0;
crt_PT_910724_Temperature_7.DocUnits = '';
crt_PT_910724_Temperature_7.Dimensions = 1;
crt_PT_910724_Temperature_7.Complexity = 'real';
crt_PT_910724_Temperature_7.SampleTime = -1;
crt_PT_910724_Temperature_7.SamplingMode = 'Sample based';
crt_PT_910724_Temperature_7.InitialValue = '';

% Frame RT_DL1MK3_Temp_6, 9504292 (0x910624)
% Signal crt_PT_910624_Temperature_6
crt_PT_910624_Temperature_6 = Simulink.Signal;
crt_PT_910624_Temperature_6.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910624_Temperature_6.RTWInfo.Alias = '';
crt_PT_910624_Temperature_6.Description = ...
  ['Frame: RT_DL1MK3_Temp_6, 9504292 (0x910624).' char(10) ...
   'Signal: Temperature_6.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910624_Temperature_6.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910624_Temperature_6.Min = 0.0;
crt_PT_910624_Temperature_6.Max = 0.0;
crt_PT_910624_Temperature_6.DocUnits = '';
crt_PT_910624_Temperature_6.Dimensions = 1;
crt_PT_910624_Temperature_6.Complexity = 'real';
crt_PT_910624_Temperature_6.SampleTime = -1;
crt_PT_910624_Temperature_6.SamplingMode = 'Sample based';
crt_PT_910624_Temperature_6.InitialValue = '';

% Frame RT_DL1MK3_Temp_5, 9504036 (0x910524)
% Signal crt_PT_910524_Temperature_5
crt_PT_910524_Temperature_5 = Simulink.Signal;
crt_PT_910524_Temperature_5.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910524_Temperature_5.RTWInfo.Alias = '';
crt_PT_910524_Temperature_5.Description = ...
  ['Frame: RT_DL1MK3_Temp_5, 9504036 (0x910524).' char(10) ...
   'Signal: Temperature_5.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910524_Temperature_5.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910524_Temperature_5.Min = 0.0;
crt_PT_910524_Temperature_5.Max = 0.0;
crt_PT_910524_Temperature_5.DocUnits = '';
crt_PT_910524_Temperature_5.Dimensions = 1;
crt_PT_910524_Temperature_5.Complexity = 'real';
crt_PT_910524_Temperature_5.SampleTime = -1;
crt_PT_910524_Temperature_5.SamplingMode = 'Sample based';
crt_PT_910524_Temperature_5.InitialValue = '';

% Frame RT_DL1MK3_Temp_4, 9503780 (0x910424)
% Signal crt_PT_910424_Temperature_4
crt_PT_910424_Temperature_4 = Simulink.Signal;
crt_PT_910424_Temperature_4.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910424_Temperature_4.RTWInfo.Alias = '';
crt_PT_910424_Temperature_4.Description = ...
  ['Frame: RT_DL1MK3_Temp_4, 9503780 (0x910424).' char(10) ...
   'Signal: Temperature_4.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910424_Temperature_4.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910424_Temperature_4.Min = 0.0;
crt_PT_910424_Temperature_4.Max = 0.0;
crt_PT_910424_Temperature_4.DocUnits = '';
crt_PT_910424_Temperature_4.Dimensions = 1;
crt_PT_910424_Temperature_4.Complexity = 'real';
crt_PT_910424_Temperature_4.SampleTime = -1;
crt_PT_910424_Temperature_4.SamplingMode = 'Sample based';
crt_PT_910424_Temperature_4.InitialValue = '';

% Frame RT_DL1MK3_Temp_3, 9503524 (0x910324)
% Signal crt_PT_910324_Temperature_3
crt_PT_910324_Temperature_3 = Simulink.Signal;
crt_PT_910324_Temperature_3.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910324_Temperature_3.RTWInfo.Alias = '';
crt_PT_910324_Temperature_3.Description = ...
  ['Frame: RT_DL1MK3_Temp_3, 9503524 (0x910324).' char(10) ...
   'Signal: Temperature_3.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910324_Temperature_3.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910324_Temperature_3.Min = 0.0;
crt_PT_910324_Temperature_3.Max = 0.0;
crt_PT_910324_Temperature_3.DocUnits = '';
crt_PT_910324_Temperature_3.Dimensions = 1;
crt_PT_910324_Temperature_3.Complexity = 'real';
crt_PT_910324_Temperature_3.SampleTime = -1;
crt_PT_910324_Temperature_3.SamplingMode = 'Sample based';
crt_PT_910324_Temperature_3.InitialValue = '';

% Frame RT_DL1MK3_Temp_2, 9503268 (0x910224)
% Signal crt_PT_910224_Temperature_2
crt_PT_910224_Temperature_2 = Simulink.Signal;
crt_PT_910224_Temperature_2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910224_Temperature_2.RTWInfo.Alias = '';
crt_PT_910224_Temperature_2.Description = ...
  ['Frame: RT_DL1MK3_Temp_2, 9503268 (0x910224).' char(10) ...
   'Signal: Temperature_2.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910224_Temperature_2.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910224_Temperature_2.Min = 0.0;
crt_PT_910224_Temperature_2.Max = 0.0;
crt_PT_910224_Temperature_2.DocUnits = '';
crt_PT_910224_Temperature_2.Dimensions = 1;
crt_PT_910224_Temperature_2.Complexity = 'real';
crt_PT_910224_Temperature_2.SampleTime = -1;
crt_PT_910224_Temperature_2.SamplingMode = 'Sample based';
crt_PT_910224_Temperature_2.InitialValue = '';

% Frame RT_DL1MK3_Temp_1, 9503012 (0x910124)
% Signal crt_PT_910124_Temperature_1
crt_PT_910124_Temperature_1 = Simulink.Signal;
crt_PT_910124_Temperature_1.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910124_Temperature_1.RTWInfo.Alias = '';
crt_PT_910124_Temperature_1.Description = ...
  ['Frame: RT_DL1MK3_Temp_1, 9503012 (0x910124).' char(10) ...
   'Signal: Temperature_1.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910124_Temperature_1.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910124_Temperature_1.Min = 0.0;
crt_PT_910124_Temperature_1.Max = 0.0;
crt_PT_910124_Temperature_1.DocUnits = '';
crt_PT_910124_Temperature_1.Dimensions = 1;
crt_PT_910124_Temperature_1.Complexity = 'real';
crt_PT_910124_Temperature_1.SampleTime = -1;
crt_PT_910124_Temperature_1.SamplingMode = 'Sample based';
crt_PT_910124_Temperature_1.InitialValue = '';

% Frame RT_DL1MK3_Analog_32, 8527652 (0x821f24)
% Signal crt_PT_821f24_Analog_32
crt_PT_821f24_Analog_32 = Simulink.Signal;
crt_PT_821f24_Analog_32.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_821f24_Analog_32.RTWInfo.Alias = '';
crt_PT_821f24_Analog_32.Description = ...
  ['Frame: RT_DL1MK3_Analog_32, 8527652 (0x821f24).' char(10) ...
   'Signal: Analog_32.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_821f24_Analog_32.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_821f24_Analog_32.Min = 0.0;
crt_PT_821f24_Analog_32.Max = 0.0;
crt_PT_821f24_Analog_32.DocUnits = '';
crt_PT_821f24_Analog_32.Dimensions = 1;
crt_PT_821f24_Analog_32.Complexity = 'real';
crt_PT_821f24_Analog_32.SampleTime = -1;
crt_PT_821f24_Analog_32.SamplingMode = 'Sample based';
crt_PT_821f24_Analog_32.InitialValue = '';

% Frame RT_DL1MK3_Analog_31, 8527396 (0x821e24)
% Signal crt_PT_821e24_Analog_31
crt_PT_821e24_Analog_31 = Simulink.Signal;
crt_PT_821e24_Analog_31.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_821e24_Analog_31.RTWInfo.Alias = '';
crt_PT_821e24_Analog_31.Description = ...
  ['Frame: RT_DL1MK3_Analog_31, 8527396 (0x821e24).' char(10) ...
   'Signal: Analog_31.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_821e24_Analog_31.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_821e24_Analog_31.Min = 0.0;
crt_PT_821e24_Analog_31.Max = 0.0;
crt_PT_821e24_Analog_31.DocUnits = '';
crt_PT_821e24_Analog_31.Dimensions = 1;
crt_PT_821e24_Analog_31.Complexity = 'real';
crt_PT_821e24_Analog_31.SampleTime = -1;
crt_PT_821e24_Analog_31.SamplingMode = 'Sample based';
crt_PT_821e24_Analog_31.InitialValue = '';

% Frame RT_DL1MK3_Analog_30, 8527140 (0x821d24)
% Signal crt_PT_821d24_Analog_30
crt_PT_821d24_Analog_30 = Simulink.Signal;
crt_PT_821d24_Analog_30.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_821d24_Analog_30.RTWInfo.Alias = '';
crt_PT_821d24_Analog_30.Description = ...
  ['Frame: RT_DL1MK3_Analog_30, 8527140 (0x821d24).' char(10) ...
   'Signal: Analog_30.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_821d24_Analog_30.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_821d24_Analog_30.Min = 0.0;
crt_PT_821d24_Analog_30.Max = 0.0;
crt_PT_821d24_Analog_30.DocUnits = '';
crt_PT_821d24_Analog_30.Dimensions = 1;
crt_PT_821d24_Analog_30.Complexity = 'real';
crt_PT_821d24_Analog_30.SampleTime = -1;
crt_PT_821d24_Analog_30.SamplingMode = 'Sample based';
crt_PT_821d24_Analog_30.InitialValue = '';

% Frame RT_DL1MK3_Analog_29, 8526884 (0x821c24)
% Signal crt_PT_821c24_Analog_29
crt_PT_821c24_Analog_29 = Simulink.Signal;
crt_PT_821c24_Analog_29.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_821c24_Analog_29.RTWInfo.Alias = '';
crt_PT_821c24_Analog_29.Description = ...
  ['Frame: RT_DL1MK3_Analog_29, 8526884 (0x821c24).' char(10) ...
   'Signal: Analog_29.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_821c24_Analog_29.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_821c24_Analog_29.Min = 0.0;
crt_PT_821c24_Analog_29.Max = 0.0;
crt_PT_821c24_Analog_29.DocUnits = '';
crt_PT_821c24_Analog_29.Dimensions = 1;
crt_PT_821c24_Analog_29.Complexity = 'real';
crt_PT_821c24_Analog_29.SampleTime = -1;
crt_PT_821c24_Analog_29.SamplingMode = 'Sample based';
crt_PT_821c24_Analog_29.InitialValue = '';

% Frame RT_DL1MK3_Analog_28, 8526628 (0x821b24)
% Signal crt_PT_821b24_Analog_28
crt_PT_821b24_Analog_28 = Simulink.Signal;
crt_PT_821b24_Analog_28.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_821b24_Analog_28.RTWInfo.Alias = '';
crt_PT_821b24_Analog_28.Description = ...
  ['Frame: RT_DL1MK3_Analog_28, 8526628 (0x821b24).' char(10) ...
   'Signal: Analog_28.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_821b24_Analog_28.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_821b24_Analog_28.Min = 0.0;
crt_PT_821b24_Analog_28.Max = 0.0;
crt_PT_821b24_Analog_28.DocUnits = '';
crt_PT_821b24_Analog_28.Dimensions = 1;
crt_PT_821b24_Analog_28.Complexity = 'real';
crt_PT_821b24_Analog_28.SampleTime = -1;
crt_PT_821b24_Analog_28.SamplingMode = 'Sample based';
crt_PT_821b24_Analog_28.InitialValue = '';

% Frame RT_DL1MK3_Analog_27, 8526372 (0x821a24)
% Signal crt_PT_821a24_Analog_27
crt_PT_821a24_Analog_27 = Simulink.Signal;
crt_PT_821a24_Analog_27.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_821a24_Analog_27.RTWInfo.Alias = '';
crt_PT_821a24_Analog_27.Description = ...
  ['Frame: RT_DL1MK3_Analog_27, 8526372 (0x821a24).' char(10) ...
   'Signal: Analog_27.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_821a24_Analog_27.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_821a24_Analog_27.Min = 0.0;
crt_PT_821a24_Analog_27.Max = 0.0;
crt_PT_821a24_Analog_27.DocUnits = '';
crt_PT_821a24_Analog_27.Dimensions = 1;
crt_PT_821a24_Analog_27.Complexity = 'real';
crt_PT_821a24_Analog_27.SampleTime = -1;
crt_PT_821a24_Analog_27.SamplingMode = 'Sample based';
crt_PT_821a24_Analog_27.InitialValue = '';

% Frame RT_DL1MK3_Analog_26, 8526116 (0x821924)
% Signal crt_PT_821924_Analog_26
crt_PT_821924_Analog_26 = Simulink.Signal;
crt_PT_821924_Analog_26.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_821924_Analog_26.RTWInfo.Alias = '';
crt_PT_821924_Analog_26.Description = ...
  ['Frame: RT_DL1MK3_Analog_26, 8526116 (0x821924).' char(10) ...
   'Signal: Analog_26.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_821924_Analog_26.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_821924_Analog_26.Min = 0.0;
crt_PT_821924_Analog_26.Max = 0.0;
crt_PT_821924_Analog_26.DocUnits = '';
crt_PT_821924_Analog_26.Dimensions = 1;
crt_PT_821924_Analog_26.Complexity = 'real';
crt_PT_821924_Analog_26.SampleTime = -1;
crt_PT_821924_Analog_26.SamplingMode = 'Sample based';
crt_PT_821924_Analog_26.InitialValue = '';

% Frame RT_DL1MK3_Analog_25, 8525860 (0x821824)
% Signal crt_PT_821824_Analog_25
crt_PT_821824_Analog_25 = Simulink.Signal;
crt_PT_821824_Analog_25.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_821824_Analog_25.RTWInfo.Alias = '';
crt_PT_821824_Analog_25.Description = ...
  ['Frame: RT_DL1MK3_Analog_25, 8525860 (0x821824).' char(10) ...
   'Signal: Analog_25.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_821824_Analog_25.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_821824_Analog_25.Min = 0.0;
crt_PT_821824_Analog_25.Max = 0.0;
crt_PT_821824_Analog_25.DocUnits = '';
crt_PT_821824_Analog_25.Dimensions = 1;
crt_PT_821824_Analog_25.Complexity = 'real';
crt_PT_821824_Analog_25.SampleTime = -1;
crt_PT_821824_Analog_25.SamplingMode = 'Sample based';
crt_PT_821824_Analog_25.InitialValue = '';

% Frame RT_DL1MK3_Analog_15, 8523300 (0x820e24)
% Signal crt_PT_820e24_Analog_15
crt_PT_820e24_Analog_15 = Simulink.Signal;
crt_PT_820e24_Analog_15.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_820e24_Analog_15.RTWInfo.Alias = '';
crt_PT_820e24_Analog_15.Description = ...
  ['Frame: RT_DL1MK3_Analog_15, 8523300 (0x820e24).' char(10) ...
   'Signal: Analog_15.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_820e24_Analog_15.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_820e24_Analog_15.Min = 0.0;
crt_PT_820e24_Analog_15.Max = 0.0;
crt_PT_820e24_Analog_15.DocUnits = '';
crt_PT_820e24_Analog_15.Dimensions = 1;
crt_PT_820e24_Analog_15.Complexity = 'real';
crt_PT_820e24_Analog_15.SampleTime = -1;
crt_PT_820e24_Analog_15.SamplingMode = 'Sample based';
crt_PT_820e24_Analog_15.InitialValue = '';

% Frame RT_DL1MK3_Analog_14, 8523044 (0x820d24)
% Signal crt_PT_820d24_Analog_14
crt_PT_820d24_Analog_14 = Simulink.Signal;
crt_PT_820d24_Analog_14.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_820d24_Analog_14.RTWInfo.Alias = '';
crt_PT_820d24_Analog_14.Description = ...
  ['Frame: RT_DL1MK3_Analog_14, 8523044 (0x820d24).' char(10) ...
   'Signal: Analog_14.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_820d24_Analog_14.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_820d24_Analog_14.Min = 0.0;
crt_PT_820d24_Analog_14.Max = 0.0;
crt_PT_820d24_Analog_14.DocUnits = '';
crt_PT_820d24_Analog_14.Dimensions = 1;
crt_PT_820d24_Analog_14.Complexity = 'real';
crt_PT_820d24_Analog_14.SampleTime = -1;
crt_PT_820d24_Analog_14.SamplingMode = 'Sample based';
crt_PT_820d24_Analog_14.InitialValue = '';

% Frame RT_DL1MK3_Analog_17, 8523812 (0x821024)
% Signal crt_PT_821024_Analog_17
crt_PT_821024_Analog_17 = Simulink.Signal;
crt_PT_821024_Analog_17.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_821024_Analog_17.RTWInfo.Alias = '';
crt_PT_821024_Analog_17.Description = ...
  ['Frame: RT_DL1MK3_Analog_17, 8523812 (0x821024).' char(10) ...
   'Signal: Analog_17.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_821024_Analog_17.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_821024_Analog_17.Min = 0.0;
crt_PT_821024_Analog_17.Max = 0.0;
crt_PT_821024_Analog_17.DocUnits = '';
crt_PT_821024_Analog_17.Dimensions = 1;
crt_PT_821024_Analog_17.Complexity = 'real';
crt_PT_821024_Analog_17.SampleTime = -1;
crt_PT_821024_Analog_17.SamplingMode = 'Sample based';
crt_PT_821024_Analog_17.InitialValue = '';

% Frame RT_DL1MK3_Analog_24, 8525604 (0x821724)
% Signal crt_PT_821724_Analog_24
crt_PT_821724_Analog_24 = Simulink.Signal;
crt_PT_821724_Analog_24.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_821724_Analog_24.RTWInfo.Alias = '';
crt_PT_821724_Analog_24.Description = ...
  ['Frame: RT_DL1MK3_Analog_24, 8525604 (0x821724).' char(10) ...
   'Signal: Analog_24.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_821724_Analog_24.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_821724_Analog_24.Min = 0.0;
crt_PT_821724_Analog_24.Max = 0.0;
crt_PT_821724_Analog_24.DocUnits = '';
crt_PT_821724_Analog_24.Dimensions = 1;
crt_PT_821724_Analog_24.Complexity = 'real';
crt_PT_821724_Analog_24.SampleTime = -1;
crt_PT_821724_Analog_24.SamplingMode = 'Sample based';
crt_PT_821724_Analog_24.InitialValue = '';

% Frame RT_DL1MK3_Analog_23, 8525348 (0x821624)
% Signal crt_PT_821624_Analog_23
crt_PT_821624_Analog_23 = Simulink.Signal;
crt_PT_821624_Analog_23.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_821624_Analog_23.RTWInfo.Alias = '';
crt_PT_821624_Analog_23.Description = ...
  ['Frame: RT_DL1MK3_Analog_23, 8525348 (0x821624).' char(10) ...
   'Signal: Analog_23.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_821624_Analog_23.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_821624_Analog_23.Min = 0.0;
crt_PT_821624_Analog_23.Max = 0.0;
crt_PT_821624_Analog_23.DocUnits = '';
crt_PT_821624_Analog_23.Dimensions = 1;
crt_PT_821624_Analog_23.Complexity = 'real';
crt_PT_821624_Analog_23.SampleTime = -1;
crt_PT_821624_Analog_23.SamplingMode = 'Sample based';
crt_PT_821624_Analog_23.InitialValue = '';

% Frame RT_DL1MK3_Analog_22, 8525092 (0x821524)
% Signal crt_PT_821524_Analog_22
crt_PT_821524_Analog_22 = Simulink.Signal;
crt_PT_821524_Analog_22.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_821524_Analog_22.RTWInfo.Alias = '';
crt_PT_821524_Analog_22.Description = ...
  ['Frame: RT_DL1MK3_Analog_22, 8525092 (0x821524).' char(10) ...
   'Signal: Analog_22.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_821524_Analog_22.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_821524_Analog_22.Min = 0.0;
crt_PT_821524_Analog_22.Max = 0.0;
crt_PT_821524_Analog_22.DocUnits = '';
crt_PT_821524_Analog_22.Dimensions = 1;
crt_PT_821524_Analog_22.Complexity = 'real';
crt_PT_821524_Analog_22.SampleTime = -1;
crt_PT_821524_Analog_22.SamplingMode = 'Sample based';
crt_PT_821524_Analog_22.InitialValue = '';

% Frame RT_DL1MK3_Analog_21, 8524836 (0x821424)
% Signal crt_PT_821424_Analog_21
crt_PT_821424_Analog_21 = Simulink.Signal;
crt_PT_821424_Analog_21.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_821424_Analog_21.RTWInfo.Alias = '';
crt_PT_821424_Analog_21.Description = ...
  ['Frame: RT_DL1MK3_Analog_21, 8524836 (0x821424).' char(10) ...
   'Signal: Analog_21.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_821424_Analog_21.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_821424_Analog_21.Min = 0.0;
crt_PT_821424_Analog_21.Max = 0.0;
crt_PT_821424_Analog_21.DocUnits = '';
crt_PT_821424_Analog_21.Dimensions = 1;
crt_PT_821424_Analog_21.Complexity = 'real';
crt_PT_821424_Analog_21.SampleTime = -1;
crt_PT_821424_Analog_21.SamplingMode = 'Sample based';
crt_PT_821424_Analog_21.InitialValue = '';

% Frame RT_DL1MK3_Analog_20, 8524580 (0x821324)
% Signal crt_PT_821324_Analog_20
crt_PT_821324_Analog_20 = Simulink.Signal;
crt_PT_821324_Analog_20.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_821324_Analog_20.RTWInfo.Alias = '';
crt_PT_821324_Analog_20.Description = ...
  ['Frame: RT_DL1MK3_Analog_20, 8524580 (0x821324).' char(10) ...
   'Signal: Analog_20.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_821324_Analog_20.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_821324_Analog_20.Min = 0.0;
crt_PT_821324_Analog_20.Max = 0.0;
crt_PT_821324_Analog_20.DocUnits = '';
crt_PT_821324_Analog_20.Dimensions = 1;
crt_PT_821324_Analog_20.Complexity = 'real';
crt_PT_821324_Analog_20.SampleTime = -1;
crt_PT_821324_Analog_20.SamplingMode = 'Sample based';
crt_PT_821324_Analog_20.InitialValue = '';

% Frame RT_DL1MK3_Analog_19, 8524324 (0x821224)
% Signal crt_PT_821224_Analog_19
crt_PT_821224_Analog_19 = Simulink.Signal;
crt_PT_821224_Analog_19.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_821224_Analog_19.RTWInfo.Alias = '';
crt_PT_821224_Analog_19.Description = ...
  ['Frame: RT_DL1MK3_Analog_19, 8524324 (0x821224).' char(10) ...
   'Signal: Analog_19.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_821224_Analog_19.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_821224_Analog_19.Min = 0.0;
crt_PT_821224_Analog_19.Max = 0.0;
crt_PT_821224_Analog_19.DocUnits = '';
crt_PT_821224_Analog_19.Dimensions = 1;
crt_PT_821224_Analog_19.Complexity = 'real';
crt_PT_821224_Analog_19.SampleTime = -1;
crt_PT_821224_Analog_19.SamplingMode = 'Sample based';
crt_PT_821224_Analog_19.InitialValue = '';

% Frame RT_DL1MK3_Analog_16, 8523556 (0x820f24)
% Signal crt_PT_820f24_Analog_16
crt_PT_820f24_Analog_16 = Simulink.Signal;
crt_PT_820f24_Analog_16.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_820f24_Analog_16.RTWInfo.Alias = '';
crt_PT_820f24_Analog_16.Description = ...
  ['Frame: RT_DL1MK3_Analog_16, 8523556 (0x820f24).' char(10) ...
   'Signal: Analog_16.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_820f24_Analog_16.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_820f24_Analog_16.Min = 0.0;
crt_PT_820f24_Analog_16.Max = 0.0;
crt_PT_820f24_Analog_16.DocUnits = '';
crt_PT_820f24_Analog_16.Dimensions = 1;
crt_PT_820f24_Analog_16.Complexity = 'real';
crt_PT_820f24_Analog_16.SampleTime = -1;
crt_PT_820f24_Analog_16.SamplingMode = 'Sample based';
crt_PT_820f24_Analog_16.InitialValue = '';

% Frame RT_DL1MK3_Analog_18, 8524068 (0x821124)
% Signal crt_PT_821124_Analog_18
crt_PT_821124_Analog_18 = Simulink.Signal;
crt_PT_821124_Analog_18.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_821124_Analog_18.RTWInfo.Alias = '';
crt_PT_821124_Analog_18.Description = ...
  ['Frame: RT_DL1MK3_Analog_18, 8524068 (0x821124).' char(10) ...
   'Signal: Analog_18.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_821124_Analog_18.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_821124_Analog_18.Min = 0.0;
crt_PT_821124_Analog_18.Max = 0.0;
crt_PT_821124_Analog_18.DocUnits = '';
crt_PT_821124_Analog_18.Dimensions = 1;
crt_PT_821124_Analog_18.Complexity = 'real';
crt_PT_821124_Analog_18.SampleTime = -1;
crt_PT_821124_Analog_18.SamplingMode = 'Sample based';
crt_PT_821124_Analog_18.InitialValue = '';

% Frame RT_DL1MK3_Analog_12, 8522532 (0x820b24)
% Signal crt_PT_820b24_Analog_12
crt_PT_820b24_Analog_12 = Simulink.Signal;
crt_PT_820b24_Analog_12.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_820b24_Analog_12.RTWInfo.Alias = '';
crt_PT_820b24_Analog_12.Description = ...
  ['Frame: RT_DL1MK3_Analog_12, 8522532 (0x820b24).' char(10) ...
   'Signal: Analog_12.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_820b24_Analog_12.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_820b24_Analog_12.Min = 0.0;
crt_PT_820b24_Analog_12.Max = 0.0;
crt_PT_820b24_Analog_12.DocUnits = '';
crt_PT_820b24_Analog_12.Dimensions = 1;
crt_PT_820b24_Analog_12.Complexity = 'real';
crt_PT_820b24_Analog_12.SampleTime = -1;
crt_PT_820b24_Analog_12.SamplingMode = 'Sample based';
crt_PT_820b24_Analog_12.InitialValue = '';

% Frame RT_DL1MK3_Analog_11, 8522276 (0x820a24)
% Signal crt_PT_820a24_Analog_11
crt_PT_820a24_Analog_11 = Simulink.Signal;
crt_PT_820a24_Analog_11.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_820a24_Analog_11.RTWInfo.Alias = '';
crt_PT_820a24_Analog_11.Description = ...
  ['Frame: RT_DL1MK3_Analog_11, 8522276 (0x820a24).' char(10) ...
   'Signal: Analog_11.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_820a24_Analog_11.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_820a24_Analog_11.Min = 0.0;
crt_PT_820a24_Analog_11.Max = 0.0;
crt_PT_820a24_Analog_11.DocUnits = '';
crt_PT_820a24_Analog_11.Dimensions = 1;
crt_PT_820a24_Analog_11.Complexity = 'real';
crt_PT_820a24_Analog_11.SampleTime = -1;
crt_PT_820a24_Analog_11.SamplingMode = 'Sample based';
crt_PT_820a24_Analog_11.InitialValue = '';

% Frame RT_DL1MK3_Analog_10, 8522020 (0x820924)
% Signal crt_PT_820924_Analog_10
crt_PT_820924_Analog_10 = Simulink.Signal;
crt_PT_820924_Analog_10.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_820924_Analog_10.RTWInfo.Alias = '';
crt_PT_820924_Analog_10.Description = ...
  ['Frame: RT_DL1MK3_Analog_10, 8522020 (0x820924).' char(10) ...
   'Signal: Analog_10.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_820924_Analog_10.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_820924_Analog_10.Min = 0.0;
crt_PT_820924_Analog_10.Max = 0.0;
crt_PT_820924_Analog_10.DocUnits = '';
crt_PT_820924_Analog_10.Dimensions = 1;
crt_PT_820924_Analog_10.Complexity = 'real';
crt_PT_820924_Analog_10.SampleTime = -1;
crt_PT_820924_Analog_10.SamplingMode = 'Sample based';
crt_PT_820924_Analog_10.InitialValue = '';

% Frame RT_DL1MK3_Analog_9, 8521764 (0x820824)
% Signal crt_PT_820824_Analog_9
crt_PT_820824_Analog_9 = Simulink.Signal;
crt_PT_820824_Analog_9.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_820824_Analog_9.RTWInfo.Alias = '';
crt_PT_820824_Analog_9.Description = ...
  ['Frame: RT_DL1MK3_Analog_9, 8521764 (0x820824).' char(10) ...
   'Signal: Analog_9.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_820824_Analog_9.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_820824_Analog_9.Min = 0.0;
crt_PT_820824_Analog_9.Max = 0.0;
crt_PT_820824_Analog_9.DocUnits = '';
crt_PT_820824_Analog_9.Dimensions = 1;
crt_PT_820824_Analog_9.Complexity = 'real';
crt_PT_820824_Analog_9.SampleTime = -1;
crt_PT_820824_Analog_9.SamplingMode = 'Sample based';
crt_PT_820824_Analog_9.InitialValue = '';

% Frame RT_DL1MK3_Analog_8, 8521508 (0x820724)
% Signal crt_PT_820724_Analog_8
crt_PT_820724_Analog_8 = Simulink.Signal;
crt_PT_820724_Analog_8.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_820724_Analog_8.RTWInfo.Alias = '';
crt_PT_820724_Analog_8.Description = ...
  ['Frame: RT_DL1MK3_Analog_8, 8521508 (0x820724).' char(10) ...
   'Signal: Analog_8.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_820724_Analog_8.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_820724_Analog_8.Min = 0.0;
crt_PT_820724_Analog_8.Max = 0.0;
crt_PT_820724_Analog_8.DocUnits = '';
crt_PT_820724_Analog_8.Dimensions = 1;
crt_PT_820724_Analog_8.Complexity = 'real';
crt_PT_820724_Analog_8.SampleTime = -1;
crt_PT_820724_Analog_8.SamplingMode = 'Sample based';
crt_PT_820724_Analog_8.InitialValue = '';

% Frame RT_DL1MK3_Analog_7, 8521252 (0x820624)
% Signal crt_PT_820624_Analog_7
crt_PT_820624_Analog_7 = Simulink.Signal;
crt_PT_820624_Analog_7.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_820624_Analog_7.RTWInfo.Alias = '';
crt_PT_820624_Analog_7.Description = ...
  ['Frame: RT_DL1MK3_Analog_7, 8521252 (0x820624).' char(10) ...
   'Signal: Analog_7.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_820624_Analog_7.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_820624_Analog_7.Min = 0.0;
crt_PT_820624_Analog_7.Max = 0.0;
crt_PT_820624_Analog_7.DocUnits = '';
crt_PT_820624_Analog_7.Dimensions = 1;
crt_PT_820624_Analog_7.Complexity = 'real';
crt_PT_820624_Analog_7.SampleTime = -1;
crt_PT_820624_Analog_7.SamplingMode = 'Sample based';
crt_PT_820624_Analog_7.InitialValue = '';

% Frame RT_DL1MK3_Analog_6, 8520996 (0x820524)
% Signal crt_PT_820524_Analog_6
crt_PT_820524_Analog_6 = Simulink.Signal;
crt_PT_820524_Analog_6.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_820524_Analog_6.RTWInfo.Alias = '';
crt_PT_820524_Analog_6.Description = ...
  ['Frame: RT_DL1MK3_Analog_6, 8520996 (0x820524).' char(10) ...
   'Signal: Analog_6.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_820524_Analog_6.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_820524_Analog_6.Min = 0.0;
crt_PT_820524_Analog_6.Max = 0.0;
crt_PT_820524_Analog_6.DocUnits = '';
crt_PT_820524_Analog_6.Dimensions = 1;
crt_PT_820524_Analog_6.Complexity = 'real';
crt_PT_820524_Analog_6.SampleTime = -1;
crt_PT_820524_Analog_6.SamplingMode = 'Sample based';
crt_PT_820524_Analog_6.InitialValue = '';

% Frame RT_DL1MK3_Analog_5, 8520740 (0x820424)
% Signal crt_PT_820424_Analog_5
crt_PT_820424_Analog_5 = Simulink.Signal;
crt_PT_820424_Analog_5.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_820424_Analog_5.RTWInfo.Alias = '';
crt_PT_820424_Analog_5.Description = ...
  ['Frame: RT_DL1MK3_Analog_5, 8520740 (0x820424).' char(10) ...
   'Signal: Analog_5.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_820424_Analog_5.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_820424_Analog_5.Min = 0.0;
crt_PT_820424_Analog_5.Max = 0.0;
crt_PT_820424_Analog_5.DocUnits = '';
crt_PT_820424_Analog_5.Dimensions = 1;
crt_PT_820424_Analog_5.Complexity = 'real';
crt_PT_820424_Analog_5.SampleTime = -1;
crt_PT_820424_Analog_5.SamplingMode = 'Sample based';
crt_PT_820424_Analog_5.InitialValue = '';

% Frame RT_DL1MK3_Analog_4, 8520484 (0x820324)
% Signal crt_PT_820324_Analog_4
crt_PT_820324_Analog_4 = Simulink.Signal;
crt_PT_820324_Analog_4.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_820324_Analog_4.RTWInfo.Alias = '';
crt_PT_820324_Analog_4.Description = ...
  ['Frame: RT_DL1MK3_Analog_4, 8520484 (0x820324).' char(10) ...
   'Signal: Analog_4.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_820324_Analog_4.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_820324_Analog_4.Min = 0.0;
crt_PT_820324_Analog_4.Max = 0.0;
crt_PT_820324_Analog_4.DocUnits = '';
crt_PT_820324_Analog_4.Dimensions = 1;
crt_PT_820324_Analog_4.Complexity = 'real';
crt_PT_820324_Analog_4.SampleTime = -1;
crt_PT_820324_Analog_4.SamplingMode = 'Sample based';
crt_PT_820324_Analog_4.InitialValue = '';

% Frame RT_DL1MK3_Analog_3, 8520228 (0x820224)
% Signal crt_PT_820224_Analog_3
crt_PT_820224_Analog_3 = Simulink.Signal;
crt_PT_820224_Analog_3.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_820224_Analog_3.RTWInfo.Alias = '';
crt_PT_820224_Analog_3.Description = ...
  ['Frame: RT_DL1MK3_Analog_3, 8520228 (0x820224).' char(10) ...
   'Signal: Analog_3.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_820224_Analog_3.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_820224_Analog_3.Min = 0.0;
crt_PT_820224_Analog_3.Max = 0.0;
crt_PT_820224_Analog_3.DocUnits = '';
crt_PT_820224_Analog_3.Dimensions = 1;
crt_PT_820224_Analog_3.Complexity = 'real';
crt_PT_820224_Analog_3.SampleTime = -1;
crt_PT_820224_Analog_3.SamplingMode = 'Sample based';
crt_PT_820224_Analog_3.InitialValue = '';

% Frame RT_DL1MK3_Analog_2, 8519972 (0x820124)
% Signal crt_PT_820124_Analog_2
crt_PT_820124_Analog_2 = Simulink.Signal;
crt_PT_820124_Analog_2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_820124_Analog_2.RTWInfo.Alias = '';
crt_PT_820124_Analog_2.Description = ...
  ['Frame: RT_DL1MK3_Analog_2, 8519972 (0x820124).' char(10) ...
   'Signal: Analog_2.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_820124_Analog_2.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_820124_Analog_2.Min = 0.0;
crt_PT_820124_Analog_2.Max = 0.0;
crt_PT_820124_Analog_2.DocUnits = '';
crt_PT_820124_Analog_2.Dimensions = 1;
crt_PT_820124_Analog_2.Complexity = 'real';
crt_PT_820124_Analog_2.SampleTime = -1;
crt_PT_820124_Analog_2.SamplingMode = 'Sample based';
crt_PT_820124_Analog_2.InitialValue = '';

% Frame RT_DL1MK3_Analog_1, 8519716 (0x820024)
% Signal crt_PT_820024_Analog_1
crt_PT_820024_Analog_1 = Simulink.Signal;
crt_PT_820024_Analog_1.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_820024_Analog_1.RTWInfo.Alias = '';
crt_PT_820024_Analog_1.Description = ...
  ['Frame: RT_DL1MK3_Analog_1, 8519716 (0x820024).' char(10) ...
   'Signal: Analog_1.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 []' ...
  ];
crt_PT_820024_Analog_1.DataType = 'fixdt(0, 16, 0.001, 0.0)';
crt_PT_820024_Analog_1.Min = 0.0;
crt_PT_820024_Analog_1.Max = 0.0;
crt_PT_820024_Analog_1.DocUnits = '';
crt_PT_820024_Analog_1.Dimensions = 1;
crt_PT_820024_Analog_1.Complexity = 'real';
crt_PT_820024_Analog_1.SampleTime = -1;
crt_PT_820024_Analog_1.SamplingMode = 'Sample based';
crt_PT_820024_Analog_1.InitialValue = '';

% Frame RT_DL1MK3_Accel, 8388644 (0x800024)
% Signal crt_PT_800024_Validity_Accel_Longitudinal
crt_PT_800024_Validity_Accel_Longitudinal = Simulink.Signal;
crt_PT_800024_Validity_Accel_Longitudinal.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800024_Validity_Accel_Longitudinal.RTWInfo.Alias = '';
crt_PT_800024_Validity_Accel_Longitudinal.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_DL1MK3_Accel, 8388644 (0x800024).' char(10) ...
   'Signal: Validity_Accel_Longitudinal.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800024_Validity_Accel_Longitudinal.DataType = 'boolean';
crt_PT_800024_Validity_Accel_Longitudinal.Min = 0.0;
crt_PT_800024_Validity_Accel_Longitudinal.Max = 1.0;
crt_PT_800024_Validity_Accel_Longitudinal.DocUnits = '';
crt_PT_800024_Validity_Accel_Longitudinal.Dimensions = 1;
crt_PT_800024_Validity_Accel_Longitudinal.Complexity = 'real';
crt_PT_800024_Validity_Accel_Longitudinal.SampleTime = -1;
crt_PT_800024_Validity_Accel_Longitudinal.SamplingMode = 'Sample based';
crt_PT_800024_Validity_Accel_Longitudinal.InitialValue = '';
% Signal crt_PT_800024_Validity_Accel_Lateral
crt_PT_800024_Validity_Accel_Lateral = Simulink.Signal;
crt_PT_800024_Validity_Accel_Lateral.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800024_Validity_Accel_Lateral.RTWInfo.Alias = '';
crt_PT_800024_Validity_Accel_Lateral.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_DL1MK3_Accel, 8388644 (0x800024).' char(10) ...
   'Signal: Validity_Accel_Lateral.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800024_Validity_Accel_Lateral.DataType = 'boolean';
crt_PT_800024_Validity_Accel_Lateral.Min = 0.0;
crt_PT_800024_Validity_Accel_Lateral.Max = 1.0;
crt_PT_800024_Validity_Accel_Lateral.DocUnits = '';
crt_PT_800024_Validity_Accel_Lateral.Dimensions = 1;
crt_PT_800024_Validity_Accel_Lateral.Complexity = 'real';
crt_PT_800024_Validity_Accel_Lateral.SampleTime = -1;
crt_PT_800024_Validity_Accel_Lateral.SamplingMode = 'Sample based';
crt_PT_800024_Validity_Accel_Lateral.InitialValue = '';
% Signal crt_PT_800024_Validity_Accel_Vertical
crt_PT_800024_Validity_Accel_Vertical = Simulink.Signal;
crt_PT_800024_Validity_Accel_Vertical.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800024_Validity_Accel_Vertical.RTWInfo.Alias = '';
crt_PT_800024_Validity_Accel_Vertical.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_DL1MK3_Accel, 8388644 (0x800024).' char(10) ...
   'Signal: Validity_Accel_Vertical.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800024_Validity_Accel_Vertical.DataType = 'boolean';
crt_PT_800024_Validity_Accel_Vertical.Min = 0.0;
crt_PT_800024_Validity_Accel_Vertical.Max = 1.0;
crt_PT_800024_Validity_Accel_Vertical.DocUnits = '';
crt_PT_800024_Validity_Accel_Vertical.Dimensions = 1;
crt_PT_800024_Validity_Accel_Vertical.Complexity = 'real';
crt_PT_800024_Validity_Accel_Vertical.SampleTime = -1;
crt_PT_800024_Validity_Accel_Vertical.SamplingMode = 'Sample based';
crt_PT_800024_Validity_Accel_Vertical.InitialValue = '';
% Signal crt_PT_800024_SQC
crt_PT_800024_SQC = Simulink.Signal;
crt_PT_800024_SQC.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800024_SQC.RTWInfo.Alias = '';
crt_PT_800024_SQC.Description = ...
  ['Sequence counter' char(10) ...
   'Frame: RT_DL1MK3_Accel, 8388644 (0x800024).' char(10) ...
   'Signal: SQC.' char(10) ...
   'Range (world values): 0.0 ... 14.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800024_SQC.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_800024_SQC.Min = 0.0;
crt_PT_800024_SQC.Max = 14.0;
crt_PT_800024_SQC.DocUnits = '';
crt_PT_800024_SQC.Dimensions = 1;
crt_PT_800024_SQC.Complexity = 'real';
crt_PT_800024_SQC.SampleTime = -1;
crt_PT_800024_SQC.SamplingMode = 'Sample based';
crt_PT_800024_SQC.InitialValue = '';
% Signal crt_PT_800024_Accuracy_Accel
crt_PT_800024_Accuracy_Accel = Simulink.Signal;
crt_PT_800024_Accuracy_Accel.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800024_Accuracy_Accel.RTWInfo.Alias = '';
crt_PT_800024_Accuracy_Accel.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_DL1MK3_Accel, 8388644 (0x800024).' char(10) ...
   'Signal: Accuracy_Accel.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800024_Accuracy_Accel.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_800024_Accuracy_Accel.Min = 0.0;
crt_PT_800024_Accuracy_Accel.Max = 255.0;
crt_PT_800024_Accuracy_Accel.DocUnits = '';
crt_PT_800024_Accuracy_Accel.Dimensions = 1;
crt_PT_800024_Accuracy_Accel.Complexity = 'real';
crt_PT_800024_Accuracy_Accel.SampleTime = -1;
crt_PT_800024_Accuracy_Accel.SamplingMode = 'Sample based';
crt_PT_800024_Accuracy_Accel.InitialValue = '';
% Signal crt_PT_800024_Accel_Longitudinal
crt_PT_800024_Accel_Longitudinal = Simulink.Signal;
crt_PT_800024_Accel_Longitudinal.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800024_Accel_Longitudinal.RTWInfo.Alias = '';
crt_PT_800024_Accel_Longitudinal.Description = ...
  ['Longitudinal acceleration.  This is positive when the vehicle accelerates in a forwards direction.' char(10) ...
   'Frame: RT_DL1MK3_Accel, 8388644 (0x800024).' char(10) ...
   'Signal: Accel_Longitudinal.' char(10) ...
   'Range (world values): -65.0 ... 65.0 [g].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [g]' ...
  ];
crt_PT_800024_Accel_Longitudinal.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_800024_Accel_Longitudinal.Min = -65.0;
crt_PT_800024_Accel_Longitudinal.Max = 65.0;
crt_PT_800024_Accel_Longitudinal.DocUnits = 'g';
crt_PT_800024_Accel_Longitudinal.Dimensions = 1;
crt_PT_800024_Accel_Longitudinal.Complexity = 'real';
crt_PT_800024_Accel_Longitudinal.SampleTime = -1;
crt_PT_800024_Accel_Longitudinal.SamplingMode = 'Sample based';
crt_PT_800024_Accel_Longitudinal.InitialValue = '';
% Signal crt_PT_800024_Accel_Lateral
crt_PT_800024_Accel_Lateral = Simulink.Signal;
crt_PT_800024_Accel_Lateral.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800024_Accel_Lateral.RTWInfo.Alias = '';
crt_PT_800024_Accel_Lateral.Description = ...
  ['Lateral acceleration.  This is positive when the vehicle accelerates towards the right, e.g. when cornering around a right-hand bend.' char(10) ...
   'Frame: RT_DL1MK3_Accel, 8388644 (0x800024).' char(10) ...
   'Signal: Accel_Lateral.' char(10) ...
   'Range (world values): -65.0 ... 65.0 [g].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [g]' ...
  ];
crt_PT_800024_Accel_Lateral.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_800024_Accel_Lateral.Min = -65.0;
crt_PT_800024_Accel_Lateral.Max = 65.0;
crt_PT_800024_Accel_Lateral.DocUnits = 'g';
crt_PT_800024_Accel_Lateral.Dimensions = 1;
crt_PT_800024_Accel_Lateral.Complexity = 'real';
crt_PT_800024_Accel_Lateral.SampleTime = -1;
crt_PT_800024_Accel_Lateral.SamplingMode = 'Sample based';
crt_PT_800024_Accel_Lateral.InitialValue = '';
% Signal crt_PT_800024_Accel_Vertical
crt_PT_800024_Accel_Vertical = Simulink.Signal;
crt_PT_800024_Accel_Vertical.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800024_Accel_Vertical.RTWInfo.Alias = '';
crt_PT_800024_Accel_Vertical.Description = ...
  ['Vertical acceleration.  This is positive when the vehicle accelerates in an upwards direction, e.g. when travelling through a dip.' char(10) ...
   'Frame: RT_DL1MK3_Accel, 8388644 (0x800024).' char(10) ...
   'Signal: Accel_Vertical.' char(10) ...
   'Range (world values): -65.0 ... 65.0 [g].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [g]' ...
  ];
crt_PT_800024_Accel_Vertical.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_800024_Accel_Vertical.Min = -65.0;
crt_PT_800024_Accel_Vertical.Max = 65.0;
crt_PT_800024_Accel_Vertical.DocUnits = 'g';
crt_PT_800024_Accel_Vertical.Dimensions = 1;
crt_PT_800024_Accel_Vertical.Complexity = 'real';
crt_PT_800024_Accel_Vertical.SampleTime = -1;
crt_PT_800024_Accel_Vertical.SamplingMode = 'Sample based';
crt_PT_800024_Accel_Vertical.InitialValue = '';

% Frame RT_SB_INS_Vpt_4_Vel_NED_2, 9384482 (0x8f3222)
% Signal crt_PT_8f3222_Virtual_4_Vel_NED_D
crt_PT_8f3222_Virtual_4_Vel_NED_D = Simulink.Signal;
crt_PT_8f3222_Virtual_4_Vel_NED_D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f3222_Virtual_4_Vel_NED_D.RTWInfo.Alias = '';
crt_PT_8f3222_Virtual_4_Vel_NED_D.Description = ...
  ['VELNED D velocity.  This is the velocity vector directly downwards towards the Earth centre at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_INS_Vpt_4_Vel_NED_2, 9384482 (0x8f3222).' char(10) ...
   'Signal: Virtual_4_Vel_NED_D.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8f3222_Virtual_4_Vel_NED_D.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8f3222_Virtual_4_Vel_NED_D.Min = -838.0;
crt_PT_8f3222_Virtual_4_Vel_NED_D.Max = 838.0;
crt_PT_8f3222_Virtual_4_Vel_NED_D.DocUnits = 'm/s';
crt_PT_8f3222_Virtual_4_Vel_NED_D.Dimensions = 1;
crt_PT_8f3222_Virtual_4_Vel_NED_D.Complexity = 'real';
crt_PT_8f3222_Virtual_4_Vel_NED_D.SampleTime = -1;
crt_PT_8f3222_Virtual_4_Vel_NED_D.SamplingMode = 'Sample based';
crt_PT_8f3222_Virtual_4_Vel_NED_D.InitialValue = '';
% Signal crt_PT_8f3222_Virtual_4_Heading
crt_PT_8f3222_Virtual_4_Heading = Simulink.Signal;
crt_PT_8f3222_Virtual_4_Heading.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f3222_Virtual_4_Heading.RTWInfo.Alias = '';
crt_PT_8f3222_Virtual_4_Heading.Description = ...
  ['This is GPS heading, the direction that the vehicle is travelling in the local horizontal plane.' char(10) ...
   'Frame: RT_SB_INS_Vpt_4_Vel_NED_2, 9384482 (0x8f3222).' char(10) ...
   'Signal: Virtual_4_Heading.' char(10) ...
   'Range (world values): -180.0 ... 180.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8f3222_Virtual_4_Heading.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8f3222_Virtual_4_Heading.Min = -180.0;
crt_PT_8f3222_Virtual_4_Heading.Max = 180.0;
crt_PT_8f3222_Virtual_4_Heading.DocUnits = 'degrees';
crt_PT_8f3222_Virtual_4_Heading.Dimensions = 1;
crt_PT_8f3222_Virtual_4_Heading.Complexity = 'real';
crt_PT_8f3222_Virtual_4_Heading.SampleTime = -1;
crt_PT_8f3222_Virtual_4_Heading.SamplingMode = 'Sample based';
crt_PT_8f3222_Virtual_4_Heading.InitialValue = '';
% Signal crt_PT_8f3222_Virtual_4_Slip
crt_PT_8f3222_Virtual_4_Slip = Simulink.Signal;
crt_PT_8f3222_Virtual_4_Slip.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f3222_Virtual_4_Slip.RTWInfo.Alias = '';
crt_PT_8f3222_Virtual_4_Slip.Description = ...
  ['Slip is defined as the difference between yaw and heading.' char(10) ...
   'Frame: RT_SB_INS_Vpt_4_Vel_NED_2, 9384482 (0x8f3222).' char(10) ...
   'Signal: Virtual_4_Slip.' char(10) ...
   'Range (world values): -180.0 ... 180.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8f3222_Virtual_4_Slip.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8f3222_Virtual_4_Slip.Min = -180.0;
crt_PT_8f3222_Virtual_4_Slip.Max = 180.0;
crt_PT_8f3222_Virtual_4_Slip.DocUnits = 'degrees';
crt_PT_8f3222_Virtual_4_Slip.Dimensions = 1;
crt_PT_8f3222_Virtual_4_Slip.Complexity = 'real';
crt_PT_8f3222_Virtual_4_Slip.SampleTime = -1;
crt_PT_8f3222_Virtual_4_Slip.SamplingMode = 'Sample based';
crt_PT_8f3222_Virtual_4_Slip.InitialValue = '';

% Frame RT_SB_INS_Vpt_4_Vel_NED_1, 9384226 (0x8f3122)
% Signal crt_PT_8f3122_Virtual_4_Vel_NED_N
crt_PT_8f3122_Virtual_4_Vel_NED_N = Simulink.Signal;
crt_PT_8f3122_Virtual_4_Vel_NED_N.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f3122_Virtual_4_Vel_NED_N.RTWInfo.Alias = '';
crt_PT_8f3122_Virtual_4_Vel_NED_N.Description = ...
  ['VELNED N velocity.  This is the velocity vector directly North at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_INS_Vpt_4_Vel_NED_1, 9384226 (0x8f3122).' char(10) ...
   'Signal: Virtual_4_Vel_NED_N.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8f3122_Virtual_4_Vel_NED_N.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8f3122_Virtual_4_Vel_NED_N.Min = -838.0;
crt_PT_8f3122_Virtual_4_Vel_NED_N.Max = 838.0;
crt_PT_8f3122_Virtual_4_Vel_NED_N.DocUnits = 'm/s';
crt_PT_8f3122_Virtual_4_Vel_NED_N.Dimensions = 1;
crt_PT_8f3122_Virtual_4_Vel_NED_N.Complexity = 'real';
crt_PT_8f3122_Virtual_4_Vel_NED_N.SampleTime = -1;
crt_PT_8f3122_Virtual_4_Vel_NED_N.SamplingMode = 'Sample based';
crt_PT_8f3122_Virtual_4_Vel_NED_N.InitialValue = '';
% Signal crt_PT_8f3122_Virtual_4_Vel_NED_E
crt_PT_8f3122_Virtual_4_Vel_NED_E = Simulink.Signal;
crt_PT_8f3122_Virtual_4_Vel_NED_E.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f3122_Virtual_4_Vel_NED_E.RTWInfo.Alias = '';
crt_PT_8f3122_Virtual_4_Vel_NED_E.Description = ...
  ['VELNED E velocity.  This is the velocity vector directly East at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_INS_Vpt_4_Vel_NED_1, 9384226 (0x8f3122).' char(10) ...
   'Signal: Virtual_4_Vel_NED_E.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8f3122_Virtual_4_Vel_NED_E.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8f3122_Virtual_4_Vel_NED_E.Min = -838.0;
crt_PT_8f3122_Virtual_4_Vel_NED_E.Max = 838.0;
crt_PT_8f3122_Virtual_4_Vel_NED_E.DocUnits = 'm/s';
crt_PT_8f3122_Virtual_4_Vel_NED_E.Dimensions = 1;
crt_PT_8f3122_Virtual_4_Vel_NED_E.Complexity = 'real';
crt_PT_8f3122_Virtual_4_Vel_NED_E.SampleTime = -1;
crt_PT_8f3122_Virtual_4_Vel_NED_E.SamplingMode = 'Sample based';
crt_PT_8f3122_Virtual_4_Vel_NED_E.InitialValue = '';

% Frame RT_SB_INS_Vpt_4_Offset, 9383970 (0x8f3022)
% Signal crt_PT_8f3022_Virtual_4_Offset_X
crt_PT_8f3022_Virtual_4_Offset_X = Simulink.Signal;
crt_PT_8f3022_Virtual_4_Offset_X.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f3022_Virtual_4_Offset_X.RTWInfo.Alias = '';
crt_PT_8f3022_Virtual_4_Offset_X.Description = ...
  ['X offset of the virtual point in the vehicle body frame.' char(10) ...
   'Frame: RT_SB_INS_Vpt_4_Offset, 9383970 (0x8f3022).' char(10) ...
   'Signal: Virtual_4_Offset_X.' char(10) ...
   'Range (world values): -32.768 ... 32.767 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8f3022_Virtual_4_Offset_X.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_8f3022_Virtual_4_Offset_X.Min = -32.768;
crt_PT_8f3022_Virtual_4_Offset_X.Max = 32.767;
crt_PT_8f3022_Virtual_4_Offset_X.DocUnits = 'm';
crt_PT_8f3022_Virtual_4_Offset_X.Dimensions = 1;
crt_PT_8f3022_Virtual_4_Offset_X.Complexity = 'real';
crt_PT_8f3022_Virtual_4_Offset_X.SampleTime = -1;
crt_PT_8f3022_Virtual_4_Offset_X.SamplingMode = 'Sample based';
crt_PT_8f3022_Virtual_4_Offset_X.InitialValue = '';
% Signal crt_PT_8f3022_Virtual_4_Offset_Y
crt_PT_8f3022_Virtual_4_Offset_Y = Simulink.Signal;
crt_PT_8f3022_Virtual_4_Offset_Y.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f3022_Virtual_4_Offset_Y.RTWInfo.Alias = '';
crt_PT_8f3022_Virtual_4_Offset_Y.Description = ...
  ['Y offset of the virtual point in the vehicle body frame.' char(10) ...
   'Frame: RT_SB_INS_Vpt_4_Offset, 9383970 (0x8f3022).' char(10) ...
   'Signal: Virtual_4_Offset_Y.' char(10) ...
   'Range (world values): -32.768 ... 32.767 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8f3022_Virtual_4_Offset_Y.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_8f3022_Virtual_4_Offset_Y.Min = -32.768;
crt_PT_8f3022_Virtual_4_Offset_Y.Max = 32.767;
crt_PT_8f3022_Virtual_4_Offset_Y.DocUnits = 'm';
crt_PT_8f3022_Virtual_4_Offset_Y.Dimensions = 1;
crt_PT_8f3022_Virtual_4_Offset_Y.Complexity = 'real';
crt_PT_8f3022_Virtual_4_Offset_Y.SampleTime = -1;
crt_PT_8f3022_Virtual_4_Offset_Y.SamplingMode = 'Sample based';
crt_PT_8f3022_Virtual_4_Offset_Y.InitialValue = '';
% Signal crt_PT_8f3022_Virtual_4_Offset_Z
crt_PT_8f3022_Virtual_4_Offset_Z = Simulink.Signal;
crt_PT_8f3022_Virtual_4_Offset_Z.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f3022_Virtual_4_Offset_Z.RTWInfo.Alias = '';
crt_PT_8f3022_Virtual_4_Offset_Z.Description = ...
  ['Z offset (+ve downwards) of the virtual point in the vehicle body frame.' char(10) ...
   'Frame: RT_SB_INS_Vpt_4_Offset, 9383970 (0x8f3022).' char(10) ...
   'Signal: Virtual_4_Offset_Z.' char(10) ...
   'Range (world values): -32.768 ... 32.767 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8f3022_Virtual_4_Offset_Z.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_8f3022_Virtual_4_Offset_Z.Min = -32.768;
crt_PT_8f3022_Virtual_4_Offset_Z.Max = 32.767;
crt_PT_8f3022_Virtual_4_Offset_Z.DocUnits = 'm';
crt_PT_8f3022_Virtual_4_Offset_Z.Dimensions = 1;
crt_PT_8f3022_Virtual_4_Offset_Z.Complexity = 'real';
crt_PT_8f3022_Virtual_4_Offset_Z.SampleTime = -1;
crt_PT_8f3022_Virtual_4_Offset_Z.SamplingMode = 'Sample based';
crt_PT_8f3022_Virtual_4_Offset_Z.InitialValue = '';

% Frame RT_SB_INS_Vpt_3_Vel_NED_2, 9380386 (0x8f2222)
% Signal crt_PT_8f2222_Virtual_3_Vel_NED_D
crt_PT_8f2222_Virtual_3_Vel_NED_D = Simulink.Signal;
crt_PT_8f2222_Virtual_3_Vel_NED_D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f2222_Virtual_3_Vel_NED_D.RTWInfo.Alias = '';
crt_PT_8f2222_Virtual_3_Vel_NED_D.Description = ...
  ['VELNED D velocity.  This is the velocity vector directly downwards towards the Earth centre at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_INS_Vpt_3_Vel_NED_2, 9380386 (0x8f2222).' char(10) ...
   'Signal: Virtual_3_Vel_NED_D.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8f2222_Virtual_3_Vel_NED_D.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8f2222_Virtual_3_Vel_NED_D.Min = -838.0;
crt_PT_8f2222_Virtual_3_Vel_NED_D.Max = 838.0;
crt_PT_8f2222_Virtual_3_Vel_NED_D.DocUnits = 'm/s';
crt_PT_8f2222_Virtual_3_Vel_NED_D.Dimensions = 1;
crt_PT_8f2222_Virtual_3_Vel_NED_D.Complexity = 'real';
crt_PT_8f2222_Virtual_3_Vel_NED_D.SampleTime = -1;
crt_PT_8f2222_Virtual_3_Vel_NED_D.SamplingMode = 'Sample based';
crt_PT_8f2222_Virtual_3_Vel_NED_D.InitialValue = '';
% Signal crt_PT_8f2222_Virtual_3_Heading
crt_PT_8f2222_Virtual_3_Heading = Simulink.Signal;
crt_PT_8f2222_Virtual_3_Heading.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f2222_Virtual_3_Heading.RTWInfo.Alias = '';
crt_PT_8f2222_Virtual_3_Heading.Description = ...
  ['This is GPS heading, the direction that the vehicle is travelling in the local horizontal plane.' char(10) ...
   'Frame: RT_SB_INS_Vpt_3_Vel_NED_2, 9380386 (0x8f2222).' char(10) ...
   'Signal: Virtual_3_Heading.' char(10) ...
   'Range (world values): -180.0 ... 180.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8f2222_Virtual_3_Heading.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8f2222_Virtual_3_Heading.Min = -180.0;
crt_PT_8f2222_Virtual_3_Heading.Max = 180.0;
crt_PT_8f2222_Virtual_3_Heading.DocUnits = 'degrees';
crt_PT_8f2222_Virtual_3_Heading.Dimensions = 1;
crt_PT_8f2222_Virtual_3_Heading.Complexity = 'real';
crt_PT_8f2222_Virtual_3_Heading.SampleTime = -1;
crt_PT_8f2222_Virtual_3_Heading.SamplingMode = 'Sample based';
crt_PT_8f2222_Virtual_3_Heading.InitialValue = '';
% Signal crt_PT_8f2222_Virtual_3_Slip
crt_PT_8f2222_Virtual_3_Slip = Simulink.Signal;
crt_PT_8f2222_Virtual_3_Slip.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f2222_Virtual_3_Slip.RTWInfo.Alias = '';
crt_PT_8f2222_Virtual_3_Slip.Description = ...
  ['Slip is defined as the difference between yaw and heading.' char(10) ...
   'Frame: RT_SB_INS_Vpt_3_Vel_NED_2, 9380386 (0x8f2222).' char(10) ...
   'Signal: Virtual_3_Slip.' char(10) ...
   'Range (world values): -180.0 ... 180.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8f2222_Virtual_3_Slip.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8f2222_Virtual_3_Slip.Min = -180.0;
crt_PT_8f2222_Virtual_3_Slip.Max = 180.0;
crt_PT_8f2222_Virtual_3_Slip.DocUnits = 'degrees';
crt_PT_8f2222_Virtual_3_Slip.Dimensions = 1;
crt_PT_8f2222_Virtual_3_Slip.Complexity = 'real';
crt_PT_8f2222_Virtual_3_Slip.SampleTime = -1;
crt_PT_8f2222_Virtual_3_Slip.SamplingMode = 'Sample based';
crt_PT_8f2222_Virtual_3_Slip.InitialValue = '';

% Frame RT_SB_INS_Vpt_3_Vel_NED_1, 9380130 (0x8f2122)
% Signal crt_PT_8f2122_Virtual_3_Vel_NED_N
crt_PT_8f2122_Virtual_3_Vel_NED_N = Simulink.Signal;
crt_PT_8f2122_Virtual_3_Vel_NED_N.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f2122_Virtual_3_Vel_NED_N.RTWInfo.Alias = '';
crt_PT_8f2122_Virtual_3_Vel_NED_N.Description = ...
  ['VELNED N velocity.  This is the velocity vector directly North at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_INS_Vpt_3_Vel_NED_1, 9380130 (0x8f2122).' char(10) ...
   'Signal: Virtual_3_Vel_NED_N.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8f2122_Virtual_3_Vel_NED_N.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8f2122_Virtual_3_Vel_NED_N.Min = -838.0;
crt_PT_8f2122_Virtual_3_Vel_NED_N.Max = 838.0;
crt_PT_8f2122_Virtual_3_Vel_NED_N.DocUnits = 'm/s';
crt_PT_8f2122_Virtual_3_Vel_NED_N.Dimensions = 1;
crt_PT_8f2122_Virtual_3_Vel_NED_N.Complexity = 'real';
crt_PT_8f2122_Virtual_3_Vel_NED_N.SampleTime = -1;
crt_PT_8f2122_Virtual_3_Vel_NED_N.SamplingMode = 'Sample based';
crt_PT_8f2122_Virtual_3_Vel_NED_N.InitialValue = '';
% Signal crt_PT_8f2122_Virtual_3_Vel_NED_E
crt_PT_8f2122_Virtual_3_Vel_NED_E = Simulink.Signal;
crt_PT_8f2122_Virtual_3_Vel_NED_E.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f2122_Virtual_3_Vel_NED_E.RTWInfo.Alias = '';
crt_PT_8f2122_Virtual_3_Vel_NED_E.Description = ...
  ['VELNED E velocity.  This is the velocity vector directly East at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_INS_Vpt_3_Vel_NED_1, 9380130 (0x8f2122).' char(10) ...
   'Signal: Virtual_3_Vel_NED_E.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8f2122_Virtual_3_Vel_NED_E.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8f2122_Virtual_3_Vel_NED_E.Min = -838.0;
crt_PT_8f2122_Virtual_3_Vel_NED_E.Max = 838.0;
crt_PT_8f2122_Virtual_3_Vel_NED_E.DocUnits = 'm/s';
crt_PT_8f2122_Virtual_3_Vel_NED_E.Dimensions = 1;
crt_PT_8f2122_Virtual_3_Vel_NED_E.Complexity = 'real';
crt_PT_8f2122_Virtual_3_Vel_NED_E.SampleTime = -1;
crt_PT_8f2122_Virtual_3_Vel_NED_E.SamplingMode = 'Sample based';
crt_PT_8f2122_Virtual_3_Vel_NED_E.InitialValue = '';

% Frame RT_SB_INS_Vpt_3_Offset, 9379874 (0x8f2022)
% Signal crt_PT_8f2022_Virtual_3_Offset_X
crt_PT_8f2022_Virtual_3_Offset_X = Simulink.Signal;
crt_PT_8f2022_Virtual_3_Offset_X.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f2022_Virtual_3_Offset_X.RTWInfo.Alias = '';
crt_PT_8f2022_Virtual_3_Offset_X.Description = ...
  ['X offset of the virtual point in the vehicle body frame.' char(10) ...
   'Frame: RT_SB_INS_Vpt_3_Offset, 9379874 (0x8f2022).' char(10) ...
   'Signal: Virtual_3_Offset_X.' char(10) ...
   'Range (world values): -32.768 ... 32.767 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8f2022_Virtual_3_Offset_X.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_8f2022_Virtual_3_Offset_X.Min = -32.768;
crt_PT_8f2022_Virtual_3_Offset_X.Max = 32.767;
crt_PT_8f2022_Virtual_3_Offset_X.DocUnits = 'm';
crt_PT_8f2022_Virtual_3_Offset_X.Dimensions = 1;
crt_PT_8f2022_Virtual_3_Offset_X.Complexity = 'real';
crt_PT_8f2022_Virtual_3_Offset_X.SampleTime = -1;
crt_PT_8f2022_Virtual_3_Offset_X.SamplingMode = 'Sample based';
crt_PT_8f2022_Virtual_3_Offset_X.InitialValue = '';
% Signal crt_PT_8f2022_Virtual_3_Offset_Y
crt_PT_8f2022_Virtual_3_Offset_Y = Simulink.Signal;
crt_PT_8f2022_Virtual_3_Offset_Y.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f2022_Virtual_3_Offset_Y.RTWInfo.Alias = '';
crt_PT_8f2022_Virtual_3_Offset_Y.Description = ...
  ['Y offset of the virtual point in the vehicle body frame.' char(10) ...
   'Frame: RT_SB_INS_Vpt_3_Offset, 9379874 (0x8f2022).' char(10) ...
   'Signal: Virtual_3_Offset_Y.' char(10) ...
   'Range (world values): -32.768 ... 32.767 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8f2022_Virtual_3_Offset_Y.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_8f2022_Virtual_3_Offset_Y.Min = -32.768;
crt_PT_8f2022_Virtual_3_Offset_Y.Max = 32.767;
crt_PT_8f2022_Virtual_3_Offset_Y.DocUnits = 'm';
crt_PT_8f2022_Virtual_3_Offset_Y.Dimensions = 1;
crt_PT_8f2022_Virtual_3_Offset_Y.Complexity = 'real';
crt_PT_8f2022_Virtual_3_Offset_Y.SampleTime = -1;
crt_PT_8f2022_Virtual_3_Offset_Y.SamplingMode = 'Sample based';
crt_PT_8f2022_Virtual_3_Offset_Y.InitialValue = '';
% Signal crt_PT_8f2022_Virtual_3_Offset_Z
crt_PT_8f2022_Virtual_3_Offset_Z = Simulink.Signal;
crt_PT_8f2022_Virtual_3_Offset_Z.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f2022_Virtual_3_Offset_Z.RTWInfo.Alias = '';
crt_PT_8f2022_Virtual_3_Offset_Z.Description = ...
  ['Z offset (+ve downwards) of the virtual point in the vehicle body frame.' char(10) ...
   'Frame: RT_SB_INS_Vpt_3_Offset, 9379874 (0x8f2022).' char(10) ...
   'Signal: Virtual_3_Offset_Z.' char(10) ...
   'Range (world values): -32.768 ... 32.767 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8f2022_Virtual_3_Offset_Z.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_8f2022_Virtual_3_Offset_Z.Min = -32.768;
crt_PT_8f2022_Virtual_3_Offset_Z.Max = 32.767;
crt_PT_8f2022_Virtual_3_Offset_Z.DocUnits = 'm';
crt_PT_8f2022_Virtual_3_Offset_Z.Dimensions = 1;
crt_PT_8f2022_Virtual_3_Offset_Z.Complexity = 'real';
crt_PT_8f2022_Virtual_3_Offset_Z.SampleTime = -1;
crt_PT_8f2022_Virtual_3_Offset_Z.SamplingMode = 'Sample based';
crt_PT_8f2022_Virtual_3_Offset_Z.InitialValue = '';

% Frame RT_SB_INS_Vpt_2_Vel_NED_2, 9376290 (0x8f1222)
% Signal crt_PT_8f1222_Virtual_2_Vel_NED_D
crt_PT_8f1222_Virtual_2_Vel_NED_D = Simulink.Signal;
crt_PT_8f1222_Virtual_2_Vel_NED_D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f1222_Virtual_2_Vel_NED_D.RTWInfo.Alias = '';
crt_PT_8f1222_Virtual_2_Vel_NED_D.Description = ...
  ['VELNED D velocity.  This is the velocity vector directly downwards towards the Earth centre at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_INS_Vpt_2_Vel_NED_2, 9376290 (0x8f1222).' char(10) ...
   'Signal: Virtual_2_Vel_NED_D.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8f1222_Virtual_2_Vel_NED_D.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8f1222_Virtual_2_Vel_NED_D.Min = -838.0;
crt_PT_8f1222_Virtual_2_Vel_NED_D.Max = 838.0;
crt_PT_8f1222_Virtual_2_Vel_NED_D.DocUnits = 'm/s';
crt_PT_8f1222_Virtual_2_Vel_NED_D.Dimensions = 1;
crt_PT_8f1222_Virtual_2_Vel_NED_D.Complexity = 'real';
crt_PT_8f1222_Virtual_2_Vel_NED_D.SampleTime = -1;
crt_PT_8f1222_Virtual_2_Vel_NED_D.SamplingMode = 'Sample based';
crt_PT_8f1222_Virtual_2_Vel_NED_D.InitialValue = '';
% Signal crt_PT_8f1222_Virtual_2_Heading
crt_PT_8f1222_Virtual_2_Heading = Simulink.Signal;
crt_PT_8f1222_Virtual_2_Heading.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f1222_Virtual_2_Heading.RTWInfo.Alias = '';
crt_PT_8f1222_Virtual_2_Heading.Description = ...
  ['This is GPS heading, the direction that the vehicle is travelling in the local horizontal plane.' char(10) ...
   'Frame: RT_SB_INS_Vpt_2_Vel_NED_2, 9376290 (0x8f1222).' char(10) ...
   'Signal: Virtual_2_Heading.' char(10) ...
   'Range (world values): -180.0 ... 180.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8f1222_Virtual_2_Heading.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8f1222_Virtual_2_Heading.Min = -180.0;
crt_PT_8f1222_Virtual_2_Heading.Max = 180.0;
crt_PT_8f1222_Virtual_2_Heading.DocUnits = 'degrees';
crt_PT_8f1222_Virtual_2_Heading.Dimensions = 1;
crt_PT_8f1222_Virtual_2_Heading.Complexity = 'real';
crt_PT_8f1222_Virtual_2_Heading.SampleTime = -1;
crt_PT_8f1222_Virtual_2_Heading.SamplingMode = 'Sample based';
crt_PT_8f1222_Virtual_2_Heading.InitialValue = '';
% Signal crt_PT_8f1222_Virtual_2_Slip
crt_PT_8f1222_Virtual_2_Slip = Simulink.Signal;
crt_PT_8f1222_Virtual_2_Slip.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f1222_Virtual_2_Slip.RTWInfo.Alias = '';
crt_PT_8f1222_Virtual_2_Slip.Description = ...
  ['Slip is defined as the difference between yaw and heading.' char(10) ...
   'Frame: RT_SB_INS_Vpt_2_Vel_NED_2, 9376290 (0x8f1222).' char(10) ...
   'Signal: Virtual_2_Slip.' char(10) ...
   'Range (world values): -180.0 ... 180.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8f1222_Virtual_2_Slip.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8f1222_Virtual_2_Slip.Min = -180.0;
crt_PT_8f1222_Virtual_2_Slip.Max = 180.0;
crt_PT_8f1222_Virtual_2_Slip.DocUnits = 'degrees';
crt_PT_8f1222_Virtual_2_Slip.Dimensions = 1;
crt_PT_8f1222_Virtual_2_Slip.Complexity = 'real';
crt_PT_8f1222_Virtual_2_Slip.SampleTime = -1;
crt_PT_8f1222_Virtual_2_Slip.SamplingMode = 'Sample based';
crt_PT_8f1222_Virtual_2_Slip.InitialValue = '';

% Frame RT_SB_INS_Vpt_2_Vel_NED_1, 9376034 (0x8f1122)
% Signal crt_PT_8f1122_Virtual_2_Vel_NED_N
crt_PT_8f1122_Virtual_2_Vel_NED_N = Simulink.Signal;
crt_PT_8f1122_Virtual_2_Vel_NED_N.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f1122_Virtual_2_Vel_NED_N.RTWInfo.Alias = '';
crt_PT_8f1122_Virtual_2_Vel_NED_N.Description = ...
  ['VELNED N velocity.  This is the velocity vector directly North at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_INS_Vpt_2_Vel_NED_1, 9376034 (0x8f1122).' char(10) ...
   'Signal: Virtual_2_Vel_NED_N.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8f1122_Virtual_2_Vel_NED_N.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8f1122_Virtual_2_Vel_NED_N.Min = -838.0;
crt_PT_8f1122_Virtual_2_Vel_NED_N.Max = 838.0;
crt_PT_8f1122_Virtual_2_Vel_NED_N.DocUnits = 'm/s';
crt_PT_8f1122_Virtual_2_Vel_NED_N.Dimensions = 1;
crt_PT_8f1122_Virtual_2_Vel_NED_N.Complexity = 'real';
crt_PT_8f1122_Virtual_2_Vel_NED_N.SampleTime = -1;
crt_PT_8f1122_Virtual_2_Vel_NED_N.SamplingMode = 'Sample based';
crt_PT_8f1122_Virtual_2_Vel_NED_N.InitialValue = '';
% Signal crt_PT_8f1122_Virtual_2_Vel_NED_E
crt_PT_8f1122_Virtual_2_Vel_NED_E = Simulink.Signal;
crt_PT_8f1122_Virtual_2_Vel_NED_E.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f1122_Virtual_2_Vel_NED_E.RTWInfo.Alias = '';
crt_PT_8f1122_Virtual_2_Vel_NED_E.Description = ...
  ['VELNED E velocity.  This is the velocity vector directly East at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_INS_Vpt_2_Vel_NED_1, 9376034 (0x8f1122).' char(10) ...
   'Signal: Virtual_2_Vel_NED_E.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8f1122_Virtual_2_Vel_NED_E.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8f1122_Virtual_2_Vel_NED_E.Min = -838.0;
crt_PT_8f1122_Virtual_2_Vel_NED_E.Max = 838.0;
crt_PT_8f1122_Virtual_2_Vel_NED_E.DocUnits = 'm/s';
crt_PT_8f1122_Virtual_2_Vel_NED_E.Dimensions = 1;
crt_PT_8f1122_Virtual_2_Vel_NED_E.Complexity = 'real';
crt_PT_8f1122_Virtual_2_Vel_NED_E.SampleTime = -1;
crt_PT_8f1122_Virtual_2_Vel_NED_E.SamplingMode = 'Sample based';
crt_PT_8f1122_Virtual_2_Vel_NED_E.InitialValue = '';

% Frame RT_SB_INS_Vpt_2_Offset, 9375778 (0x8f1022)
% Signal crt_PT_8f1022_Virtual_2_Offset_X
crt_PT_8f1022_Virtual_2_Offset_X = Simulink.Signal;
crt_PT_8f1022_Virtual_2_Offset_X.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f1022_Virtual_2_Offset_X.RTWInfo.Alias = '';
crt_PT_8f1022_Virtual_2_Offset_X.Description = ...
  ['X offset of the virtual point in the vehicle body frame.' char(10) ...
   'Frame: RT_SB_INS_Vpt_2_Offset, 9375778 (0x8f1022).' char(10) ...
   'Signal: Virtual_2_Offset_X.' char(10) ...
   'Range (world values): -32.768 ... 32.767 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8f1022_Virtual_2_Offset_X.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_8f1022_Virtual_2_Offset_X.Min = -32.768;
crt_PT_8f1022_Virtual_2_Offset_X.Max = 32.767;
crt_PT_8f1022_Virtual_2_Offset_X.DocUnits = 'm';
crt_PT_8f1022_Virtual_2_Offset_X.Dimensions = 1;
crt_PT_8f1022_Virtual_2_Offset_X.Complexity = 'real';
crt_PT_8f1022_Virtual_2_Offset_X.SampleTime = -1;
crt_PT_8f1022_Virtual_2_Offset_X.SamplingMode = 'Sample based';
crt_PT_8f1022_Virtual_2_Offset_X.InitialValue = '';
% Signal crt_PT_8f1022_Virtual_2_Offset_Y
crt_PT_8f1022_Virtual_2_Offset_Y = Simulink.Signal;
crt_PT_8f1022_Virtual_2_Offset_Y.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f1022_Virtual_2_Offset_Y.RTWInfo.Alias = '';
crt_PT_8f1022_Virtual_2_Offset_Y.Description = ...
  ['Y offset of the virtual point in the vehicle body frame.' char(10) ...
   'Frame: RT_SB_INS_Vpt_2_Offset, 9375778 (0x8f1022).' char(10) ...
   'Signal: Virtual_2_Offset_Y.' char(10) ...
   'Range (world values): -32.768 ... 32.767 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8f1022_Virtual_2_Offset_Y.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_8f1022_Virtual_2_Offset_Y.Min = -32.768;
crt_PT_8f1022_Virtual_2_Offset_Y.Max = 32.767;
crt_PT_8f1022_Virtual_2_Offset_Y.DocUnits = 'm';
crt_PT_8f1022_Virtual_2_Offset_Y.Dimensions = 1;
crt_PT_8f1022_Virtual_2_Offset_Y.Complexity = 'real';
crt_PT_8f1022_Virtual_2_Offset_Y.SampleTime = -1;
crt_PT_8f1022_Virtual_2_Offset_Y.SamplingMode = 'Sample based';
crt_PT_8f1022_Virtual_2_Offset_Y.InitialValue = '';
% Signal crt_PT_8f1022_Virtual_2_Offset_Z
crt_PT_8f1022_Virtual_2_Offset_Z = Simulink.Signal;
crt_PT_8f1022_Virtual_2_Offset_Z.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f1022_Virtual_2_Offset_Z.RTWInfo.Alias = '';
crt_PT_8f1022_Virtual_2_Offset_Z.Description = ...
  ['Z offset (+ve downwards) of the virtual point in the vehicle body frame.' char(10) ...
   'Frame: RT_SB_INS_Vpt_2_Offset, 9375778 (0x8f1022).' char(10) ...
   'Signal: Virtual_2_Offset_Z.' char(10) ...
   'Range (world values): -32.768 ... 32.767 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8f1022_Virtual_2_Offset_Z.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_8f1022_Virtual_2_Offset_Z.Min = -32.768;
crt_PT_8f1022_Virtual_2_Offset_Z.Max = 32.767;
crt_PT_8f1022_Virtual_2_Offset_Z.DocUnits = 'm';
crt_PT_8f1022_Virtual_2_Offset_Z.Dimensions = 1;
crt_PT_8f1022_Virtual_2_Offset_Z.Complexity = 'real';
crt_PT_8f1022_Virtual_2_Offset_Z.SampleTime = -1;
crt_PT_8f1022_Virtual_2_Offset_Z.SamplingMode = 'Sample based';
crt_PT_8f1022_Virtual_2_Offset_Z.InitialValue = '';

% Frame RT_SB_INS_Vpt_1_Vel_NED_2, 9372194 (0x8f0222)
% Signal crt_PT_8f0222_Virtual_1_Vel_NED_D
crt_PT_8f0222_Virtual_1_Vel_NED_D = Simulink.Signal;
crt_PT_8f0222_Virtual_1_Vel_NED_D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f0222_Virtual_1_Vel_NED_D.RTWInfo.Alias = '';
crt_PT_8f0222_Virtual_1_Vel_NED_D.Description = ...
  ['VELNED D velocity.  This is the velocity vector directly downwards towards the Earth centre at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_INS_Vpt_1_Vel_NED_2, 9372194 (0x8f0222).' char(10) ...
   'Signal: Virtual_1_Vel_NED_D.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8f0222_Virtual_1_Vel_NED_D.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8f0222_Virtual_1_Vel_NED_D.Min = -838.0;
crt_PT_8f0222_Virtual_1_Vel_NED_D.Max = 838.0;
crt_PT_8f0222_Virtual_1_Vel_NED_D.DocUnits = 'm/s';
crt_PT_8f0222_Virtual_1_Vel_NED_D.Dimensions = 1;
crt_PT_8f0222_Virtual_1_Vel_NED_D.Complexity = 'real';
crt_PT_8f0222_Virtual_1_Vel_NED_D.SampleTime = -1;
crt_PT_8f0222_Virtual_1_Vel_NED_D.SamplingMode = 'Sample based';
crt_PT_8f0222_Virtual_1_Vel_NED_D.InitialValue = '';
% Signal crt_PT_8f0222_Virtual_1_Heading
crt_PT_8f0222_Virtual_1_Heading = Simulink.Signal;
crt_PT_8f0222_Virtual_1_Heading.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f0222_Virtual_1_Heading.RTWInfo.Alias = '';
crt_PT_8f0222_Virtual_1_Heading.Description = ...
  ['This is GPS heading, the direction that the vehicle is travelling in the local horizontal plane.' char(10) ...
   'Frame: RT_SB_INS_Vpt_1_Vel_NED_2, 9372194 (0x8f0222).' char(10) ...
   'Signal: Virtual_1_Heading.' char(10) ...
   'Range (world values): -180.0 ... 180.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8f0222_Virtual_1_Heading.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8f0222_Virtual_1_Heading.Min = -180.0;
crt_PT_8f0222_Virtual_1_Heading.Max = 180.0;
crt_PT_8f0222_Virtual_1_Heading.DocUnits = 'degrees';
crt_PT_8f0222_Virtual_1_Heading.Dimensions = 1;
crt_PT_8f0222_Virtual_1_Heading.Complexity = 'real';
crt_PT_8f0222_Virtual_1_Heading.SampleTime = -1;
crt_PT_8f0222_Virtual_1_Heading.SamplingMode = 'Sample based';
crt_PT_8f0222_Virtual_1_Heading.InitialValue = '';
% Signal crt_PT_8f0222_Virtual_1_Slip
crt_PT_8f0222_Virtual_1_Slip = Simulink.Signal;
crt_PT_8f0222_Virtual_1_Slip.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f0222_Virtual_1_Slip.RTWInfo.Alias = '';
crt_PT_8f0222_Virtual_1_Slip.Description = ...
  ['Slip is defined as the difference between yaw and heading.' char(10) ...
   'Frame: RT_SB_INS_Vpt_1_Vel_NED_2, 9372194 (0x8f0222).' char(10) ...
   'Signal: Virtual_1_Slip.' char(10) ...
   'Range (world values): -180.0 ... 180.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8f0222_Virtual_1_Slip.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8f0222_Virtual_1_Slip.Min = -180.0;
crt_PT_8f0222_Virtual_1_Slip.Max = 180.0;
crt_PT_8f0222_Virtual_1_Slip.DocUnits = 'degrees';
crt_PT_8f0222_Virtual_1_Slip.Dimensions = 1;
crt_PT_8f0222_Virtual_1_Slip.Complexity = 'real';
crt_PT_8f0222_Virtual_1_Slip.SampleTime = -1;
crt_PT_8f0222_Virtual_1_Slip.SamplingMode = 'Sample based';
crt_PT_8f0222_Virtual_1_Slip.InitialValue = '';

% Frame RT_SB_INS_Vpt_1_Vel_NED_1, 9371938 (0x8f0122)
% Signal crt_PT_8f0122_Virtual_1_Vel_NED_N
crt_PT_8f0122_Virtual_1_Vel_NED_N = Simulink.Signal;
crt_PT_8f0122_Virtual_1_Vel_NED_N.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f0122_Virtual_1_Vel_NED_N.RTWInfo.Alias = '';
crt_PT_8f0122_Virtual_1_Vel_NED_N.Description = ...
  ['VELNED N velocity.  This is the velocity vector directly North at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_INS_Vpt_1_Vel_NED_1, 9371938 (0x8f0122).' char(10) ...
   'Signal: Virtual_1_Vel_NED_N.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8f0122_Virtual_1_Vel_NED_N.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8f0122_Virtual_1_Vel_NED_N.Min = -838.0;
crt_PT_8f0122_Virtual_1_Vel_NED_N.Max = 838.0;
crt_PT_8f0122_Virtual_1_Vel_NED_N.DocUnits = 'm/s';
crt_PT_8f0122_Virtual_1_Vel_NED_N.Dimensions = 1;
crt_PT_8f0122_Virtual_1_Vel_NED_N.Complexity = 'real';
crt_PT_8f0122_Virtual_1_Vel_NED_N.SampleTime = -1;
crt_PT_8f0122_Virtual_1_Vel_NED_N.SamplingMode = 'Sample based';
crt_PT_8f0122_Virtual_1_Vel_NED_N.InitialValue = '';
% Signal crt_PT_8f0122_Virtual_1_Vel_NED_E
crt_PT_8f0122_Virtual_1_Vel_NED_E = Simulink.Signal;
crt_PT_8f0122_Virtual_1_Vel_NED_E.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f0122_Virtual_1_Vel_NED_E.RTWInfo.Alias = '';
crt_PT_8f0122_Virtual_1_Vel_NED_E.Description = ...
  ['VELNED E velocity.  This is the velocity vector directly East at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_INS_Vpt_1_Vel_NED_1, 9371938 (0x8f0122).' char(10) ...
   'Signal: Virtual_1_Vel_NED_E.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8f0122_Virtual_1_Vel_NED_E.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8f0122_Virtual_1_Vel_NED_E.Min = -838.0;
crt_PT_8f0122_Virtual_1_Vel_NED_E.Max = 838.0;
crt_PT_8f0122_Virtual_1_Vel_NED_E.DocUnits = 'm/s';
crt_PT_8f0122_Virtual_1_Vel_NED_E.Dimensions = 1;
crt_PT_8f0122_Virtual_1_Vel_NED_E.Complexity = 'real';
crt_PT_8f0122_Virtual_1_Vel_NED_E.SampleTime = -1;
crt_PT_8f0122_Virtual_1_Vel_NED_E.SamplingMode = 'Sample based';
crt_PT_8f0122_Virtual_1_Vel_NED_E.InitialValue = '';

% Frame RT_SB_INS_Vpt_1_Offset, 9371682 (0x8f0022)
% Signal crt_PT_8f0022_Virtual_1_Offset_X
crt_PT_8f0022_Virtual_1_Offset_X = Simulink.Signal;
crt_PT_8f0022_Virtual_1_Offset_X.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f0022_Virtual_1_Offset_X.RTWInfo.Alias = '';
crt_PT_8f0022_Virtual_1_Offset_X.Description = ...
  ['X offset of the virtual point in the vehicle body frame.' char(10) ...
   'Frame: RT_SB_INS_Vpt_1_Offset, 9371682 (0x8f0022).' char(10) ...
   'Signal: Virtual_1_Offset_X.' char(10) ...
   'Range (world values): -32.768 ... 32.767 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8f0022_Virtual_1_Offset_X.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_8f0022_Virtual_1_Offset_X.Min = -32.768;
crt_PT_8f0022_Virtual_1_Offset_X.Max = 32.767;
crt_PT_8f0022_Virtual_1_Offset_X.DocUnits = 'm';
crt_PT_8f0022_Virtual_1_Offset_X.Dimensions = 1;
crt_PT_8f0022_Virtual_1_Offset_X.Complexity = 'real';
crt_PT_8f0022_Virtual_1_Offset_X.SampleTime = -1;
crt_PT_8f0022_Virtual_1_Offset_X.SamplingMode = 'Sample based';
crt_PT_8f0022_Virtual_1_Offset_X.InitialValue = '';
% Signal crt_PT_8f0022_Virtual_1_Offset_Y
crt_PT_8f0022_Virtual_1_Offset_Y = Simulink.Signal;
crt_PT_8f0022_Virtual_1_Offset_Y.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f0022_Virtual_1_Offset_Y.RTWInfo.Alias = '';
crt_PT_8f0022_Virtual_1_Offset_Y.Description = ...
  ['Y offset of the virtual point in the vehicle body frame.' char(10) ...
   'Frame: RT_SB_INS_Vpt_1_Offset, 9371682 (0x8f0022).' char(10) ...
   'Signal: Virtual_1_Offset_Y.' char(10) ...
   'Range (world values): -32.768 ... 32.767 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8f0022_Virtual_1_Offset_Y.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_8f0022_Virtual_1_Offset_Y.Min = -32.768;
crt_PT_8f0022_Virtual_1_Offset_Y.Max = 32.767;
crt_PT_8f0022_Virtual_1_Offset_Y.DocUnits = 'm';
crt_PT_8f0022_Virtual_1_Offset_Y.Dimensions = 1;
crt_PT_8f0022_Virtual_1_Offset_Y.Complexity = 'real';
crt_PT_8f0022_Virtual_1_Offset_Y.SampleTime = -1;
crt_PT_8f0022_Virtual_1_Offset_Y.SamplingMode = 'Sample based';
crt_PT_8f0022_Virtual_1_Offset_Y.InitialValue = '';
% Signal crt_PT_8f0022_Virtual_1_Offset_Z
crt_PT_8f0022_Virtual_1_Offset_Z = Simulink.Signal;
crt_PT_8f0022_Virtual_1_Offset_Z.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8f0022_Virtual_1_Offset_Z.RTWInfo.Alias = '';
crt_PT_8f0022_Virtual_1_Offset_Z.Description = ...
  ['Z offset (+ve downwards) of the virtual point in the vehicle body frame.' char(10) ...
   'Frame: RT_SB_INS_Vpt_1_Offset, 9371682 (0x8f0022).' char(10) ...
   'Signal: Virtual_1_Offset_Z.' char(10) ...
   'Range (world values): -32.768 ... 32.767 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8f0022_Virtual_1_Offset_Z.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_8f0022_Virtual_1_Offset_Z.Min = -32.768;
crt_PT_8f0022_Virtual_1_Offset_Z.Max = 32.767;
crt_PT_8f0022_Virtual_1_Offset_Z.DocUnits = 'm';
crt_PT_8f0022_Virtual_1_Offset_Z.Dimensions = 1;
crt_PT_8f0022_Virtual_1_Offset_Z.Complexity = 'real';
crt_PT_8f0022_Virtual_1_Offset_Z.SampleTime = -1;
crt_PT_8f0022_Virtual_1_Offset_Z.SamplingMode = 'Sample based';
crt_PT_8f0022_Virtual_1_Offset_Z.InitialValue = '';

% Frame RT_SB_INS_Slip, 9311778 (0x8e1622)
% Signal crt_PT_8e1622_Validity_INS_Slip
crt_PT_8e1622_Validity_INS_Slip = Simulink.Signal;
crt_PT_8e1622_Validity_INS_Slip.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1622_Validity_INS_Slip.RTWInfo.Alias = '';
crt_PT_8e1622_Validity_INS_Slip.Description = ...
  ['Frame: RT_SB_INS_Slip, 9311778 (0x8e1622).' char(10) ...
   'Signal: Validity_INS_Slip.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1622_Validity_INS_Slip.DataType = 'boolean';
crt_PT_8e1622_Validity_INS_Slip.Min = 0.0;
crt_PT_8e1622_Validity_INS_Slip.Max = 1.0;
crt_PT_8e1622_Validity_INS_Slip.DocUnits = '';
crt_PT_8e1622_Validity_INS_Slip.Dimensions = 1;
crt_PT_8e1622_Validity_INS_Slip.Complexity = 'real';
crt_PT_8e1622_Validity_INS_Slip.SampleTime = -1;
crt_PT_8e1622_Validity_INS_Slip.SamplingMode = 'Sample based';
crt_PT_8e1622_Validity_INS_Slip.InitialValue = '';
% Signal crt_PT_8e1622_Validity_INS_Squat
crt_PT_8e1622_Validity_INS_Squat = Simulink.Signal;
crt_PT_8e1622_Validity_INS_Squat.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1622_Validity_INS_Squat.RTWInfo.Alias = '';
crt_PT_8e1622_Validity_INS_Squat.Description = ...
  ['Frame: RT_SB_INS_Slip, 9311778 (0x8e1622).' char(10) ...
   'Signal: Validity_INS_Squat.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1622_Validity_INS_Squat.DataType = 'boolean';
crt_PT_8e1622_Validity_INS_Squat.Min = 0.0;
crt_PT_8e1622_Validity_INS_Squat.Max = 1.0;
crt_PT_8e1622_Validity_INS_Squat.DocUnits = '';
crt_PT_8e1622_Validity_INS_Squat.Dimensions = 1;
crt_PT_8e1622_Validity_INS_Squat.Complexity = 'real';
crt_PT_8e1622_Validity_INS_Squat.SampleTime = -1;
crt_PT_8e1622_Validity_INS_Squat.SamplingMode = 'Sample based';
crt_PT_8e1622_Validity_INS_Squat.InitialValue = '';
% Signal crt_PT_8e1622_Accuracy_INS_Slip
crt_PT_8e1622_Accuracy_INS_Slip = Simulink.Signal;
crt_PT_8e1622_Accuracy_INS_Slip.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1622_Accuracy_INS_Slip.RTWInfo.Alias = '';
crt_PT_8e1622_Accuracy_INS_Slip.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_INS_Slip, 9311778 (0x8e1622).' char(10) ...
   'Signal: Accuracy_INS_Slip.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1622_Accuracy_INS_Slip.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e1622_Accuracy_INS_Slip.Min = 0.0;
crt_PT_8e1622_Accuracy_INS_Slip.Max = 255.0;
crt_PT_8e1622_Accuracy_INS_Slip.DocUnits = '';
crt_PT_8e1622_Accuracy_INS_Slip.Dimensions = 1;
crt_PT_8e1622_Accuracy_INS_Slip.Complexity = 'real';
crt_PT_8e1622_Accuracy_INS_Slip.SampleTime = -1;
crt_PT_8e1622_Accuracy_INS_Slip.SamplingMode = 'Sample based';
crt_PT_8e1622_Accuracy_INS_Slip.InitialValue = '';
% Signal crt_PT_8e1622_INS_Slip
crt_PT_8e1622_INS_Slip = Simulink.Signal;
crt_PT_8e1622_INS_Slip.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1622_INS_Slip.RTWInfo.Alias = '';
crt_PT_8e1622_INS_Slip.Description = ...
  ['Slip is defined as the difference between yaw and heading' char(10) ...
   'Frame: RT_SB_INS_Slip, 9311778 (0x8e1622).' char(10) ...
   'Signal: INS_Slip.' char(10) ...
   'Range (world values): -360.0 ... 360.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8e1622_INS_Slip.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8e1622_INS_Slip.Min = -360.0;
crt_PT_8e1622_INS_Slip.Max = 360.0;
crt_PT_8e1622_INS_Slip.DocUnits = 'degrees';
crt_PT_8e1622_INS_Slip.Dimensions = 1;
crt_PT_8e1622_INS_Slip.Complexity = 'real';
crt_PT_8e1622_INS_Slip.SampleTime = -1;
crt_PT_8e1622_INS_Slip.SamplingMode = 'Sample based';
crt_PT_8e1622_INS_Slip.InitialValue = '';
% Signal crt_PT_8e1622_Accuracy_INS_Squat
crt_PT_8e1622_Accuracy_INS_Squat = Simulink.Signal;
crt_PT_8e1622_Accuracy_INS_Squat.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1622_Accuracy_INS_Squat.RTWInfo.Alias = '';
crt_PT_8e1622_Accuracy_INS_Squat.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_INS_Slip, 9311778 (0x8e1622).' char(10) ...
   'Signal: Accuracy_INS_Squat.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1622_Accuracy_INS_Squat.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e1622_Accuracy_INS_Squat.Min = 0.0;
crt_PT_8e1622_Accuracy_INS_Squat.Max = 255.0;
crt_PT_8e1622_Accuracy_INS_Squat.DocUnits = '';
crt_PT_8e1622_Accuracy_INS_Squat.Dimensions = 1;
crt_PT_8e1622_Accuracy_INS_Squat.Complexity = 'real';
crt_PT_8e1622_Accuracy_INS_Squat.SampleTime = -1;
crt_PT_8e1622_Accuracy_INS_Squat.SamplingMode = 'Sample based';
crt_PT_8e1622_Accuracy_INS_Squat.InitialValue = '';
% Signal crt_PT_8e1622_INS_Squat
crt_PT_8e1622_INS_Squat = Simulink.Signal;
crt_PT_8e1622_INS_Squat.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1622_INS_Squat.RTWInfo.Alias = '';
crt_PT_8e1622_INS_Squat.Description = ...
  ['Squat is defined as the difference between pitch and gradient' char(10) ...
   'Frame: RT_SB_INS_Slip, 9311778 (0x8e1622).' char(10) ...
   'Signal: INS_Squat.' char(10) ...
   'Range (world values): -360.0 ... 360.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8e1622_INS_Squat.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8e1622_INS_Squat.Min = -360.0;
crt_PT_8e1622_INS_Squat.Max = 360.0;
crt_PT_8e1622_INS_Squat.DocUnits = 'degrees';
crt_PT_8e1622_INS_Squat.Dimensions = 1;
crt_PT_8e1622_INS_Squat.Complexity = 'real';
crt_PT_8e1622_INS_Squat.SampleTime = -1;
crt_PT_8e1622_INS_Squat.SamplingMode = 'Sample based';
crt_PT_8e1622_INS_Squat.InitialValue = '';

% Frame RT_SB_INS_Vel_ECEF_2, 9311010 (0x8e1322)
% Signal crt_PT_8e1322_Validity_INS_Vel_ECEF_Y
crt_PT_8e1322_Validity_INS_Vel_ECEF_Y = Simulink.Signal;
crt_PT_8e1322_Validity_INS_Vel_ECEF_Y.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1322_Validity_INS_Vel_ECEF_Y.RTWInfo.Alias = '';
crt_PT_8e1322_Validity_INS_Vel_ECEF_Y.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_INS_Vel_ECEF_2, 9311010 (0x8e1322).' char(10) ...
   'Signal: Validity_INS_Vel_ECEF_Y.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1322_Validity_INS_Vel_ECEF_Y.DataType = 'boolean';
crt_PT_8e1322_Validity_INS_Vel_ECEF_Y.Min = 0.0;
crt_PT_8e1322_Validity_INS_Vel_ECEF_Y.Max = 1.0;
crt_PT_8e1322_Validity_INS_Vel_ECEF_Y.DocUnits = '';
crt_PT_8e1322_Validity_INS_Vel_ECEF_Y.Dimensions = 1;
crt_PT_8e1322_Validity_INS_Vel_ECEF_Y.Complexity = 'real';
crt_PT_8e1322_Validity_INS_Vel_ECEF_Y.SampleTime = -1;
crt_PT_8e1322_Validity_INS_Vel_ECEF_Y.SamplingMode = 'Sample based';
crt_PT_8e1322_Validity_INS_Vel_ECEF_Y.InitialValue = '';
% Signal crt_PT_8e1322_Validity_INS_Vel_ECEF_Z
crt_PT_8e1322_Validity_INS_Vel_ECEF_Z = Simulink.Signal;
crt_PT_8e1322_Validity_INS_Vel_ECEF_Z.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1322_Validity_INS_Vel_ECEF_Z.RTWInfo.Alias = '';
crt_PT_8e1322_Validity_INS_Vel_ECEF_Z.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_INS_Vel_ECEF_2, 9311010 (0x8e1322).' char(10) ...
   'Signal: Validity_INS_Vel_ECEF_Z.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1322_Validity_INS_Vel_ECEF_Z.DataType = 'boolean';
crt_PT_8e1322_Validity_INS_Vel_ECEF_Z.Min = 0.0;
crt_PT_8e1322_Validity_INS_Vel_ECEF_Z.Max = 1.0;
crt_PT_8e1322_Validity_INS_Vel_ECEF_Z.DocUnits = '';
crt_PT_8e1322_Validity_INS_Vel_ECEF_Z.Dimensions = 1;
crt_PT_8e1322_Validity_INS_Vel_ECEF_Z.Complexity = 'real';
crt_PT_8e1322_Validity_INS_Vel_ECEF_Z.SampleTime = -1;
crt_PT_8e1322_Validity_INS_Vel_ECEF_Z.SamplingMode = 'Sample based';
crt_PT_8e1322_Validity_INS_Vel_ECEF_Z.InitialValue = '';
% Signal crt_PT_8e1322_INS_Vel_ECEF_Y
crt_PT_8e1322_INS_Vel_ECEF_Y = Simulink.Signal;
crt_PT_8e1322_INS_Vel_ECEF_Y.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1322_INS_Vel_ECEF_Y.RTWInfo.Alias = '';
crt_PT_8e1322_INS_Vel_ECEF_Y.Description = ...
  ['ECEF Y velocity.  The ECEF Y axis originates from the Earth centre, and the positive Y axis intersects the Earth surface at zero degrees latittude and 90 degrees longitude.' char(10) ...
   'Frame: RT_SB_INS_Vel_ECEF_2, 9311010 (0x8e1322).' char(10) ...
   'Signal: INS_Vel_ECEF_Y.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8e1322_INS_Vel_ECEF_Y.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8e1322_INS_Vel_ECEF_Y.Min = -838.0;
crt_PT_8e1322_INS_Vel_ECEF_Y.Max = 838.0;
crt_PT_8e1322_INS_Vel_ECEF_Y.DocUnits = 'm/s';
crt_PT_8e1322_INS_Vel_ECEF_Y.Dimensions = 1;
crt_PT_8e1322_INS_Vel_ECEF_Y.Complexity = 'real';
crt_PT_8e1322_INS_Vel_ECEF_Y.SampleTime = -1;
crt_PT_8e1322_INS_Vel_ECEF_Y.SamplingMode = 'Sample based';
crt_PT_8e1322_INS_Vel_ECEF_Y.InitialValue = '';
% Signal crt_PT_8e1322_INS_Vel_ECEF_Z
crt_PT_8e1322_INS_Vel_ECEF_Z = Simulink.Signal;
crt_PT_8e1322_INS_Vel_ECEF_Z.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1322_INS_Vel_ECEF_Z.RTWInfo.Alias = '';
crt_PT_8e1322_INS_Vel_ECEF_Z.Description = ...
  ['ECEF Z velocity.  The ECEF Z axis originates from the Earth centre, and the positive Z axis intersects the Earth surface at the North Pole.' char(10) ...
   'Frame: RT_SB_INS_Vel_ECEF_2, 9311010 (0x8e1322).' char(10) ...
   'Signal: INS_Vel_ECEF_Z.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8e1322_INS_Vel_ECEF_Z.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8e1322_INS_Vel_ECEF_Z.Min = -838.0;
crt_PT_8e1322_INS_Vel_ECEF_Z.Max = 838.0;
crt_PT_8e1322_INS_Vel_ECEF_Z.DocUnits = 'm/s';
crt_PT_8e1322_INS_Vel_ECEF_Z.Dimensions = 1;
crt_PT_8e1322_INS_Vel_ECEF_Z.Complexity = 'real';
crt_PT_8e1322_INS_Vel_ECEF_Z.SampleTime = -1;
crt_PT_8e1322_INS_Vel_ECEF_Z.SamplingMode = 'Sample based';
crt_PT_8e1322_INS_Vel_ECEF_Z.InitialValue = '';

% Frame RT_SB_INS_Vel_ECEF_1, 9310754 (0x8e1222)
% Signal crt_PT_8e1222_Validity_INS_Vel_ECEF_X
crt_PT_8e1222_Validity_INS_Vel_ECEF_X = Simulink.Signal;
crt_PT_8e1222_Validity_INS_Vel_ECEF_X.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1222_Validity_INS_Vel_ECEF_X.RTWInfo.Alias = '';
crt_PT_8e1222_Validity_INS_Vel_ECEF_X.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_INS_Vel_ECEF_1, 9310754 (0x8e1222).' char(10) ...
   'Signal: Validity_INS_Vel_ECEF_X.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1222_Validity_INS_Vel_ECEF_X.DataType = 'boolean';
crt_PT_8e1222_Validity_INS_Vel_ECEF_X.Min = 0.0;
crt_PT_8e1222_Validity_INS_Vel_ECEF_X.Max = 1.0;
crt_PT_8e1222_Validity_INS_Vel_ECEF_X.DocUnits = '';
crt_PT_8e1222_Validity_INS_Vel_ECEF_X.Dimensions = 1;
crt_PT_8e1222_Validity_INS_Vel_ECEF_X.Complexity = 'real';
crt_PT_8e1222_Validity_INS_Vel_ECEF_X.SampleTime = -1;
crt_PT_8e1222_Validity_INS_Vel_ECEF_X.SamplingMode = 'Sample based';
crt_PT_8e1222_Validity_INS_Vel_ECEF_X.InitialValue = '';
% Signal crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X = Simulink.Signal;
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X.RTWInfo.Alias = '';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X.Description = ...
  ['Frame: RT_SB_INS_Vel_ECEF_1, 9310754 (0x8e1222).' char(10) ...
   'Signal: Accuracy_INS_Vel_ECEF_X.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X.Min = 0.0;
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X.Max = 255.0;
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X.DocUnits = '';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X.Dimensions = 1;
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X.Complexity = 'real';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X.SampleTime = -1;
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X.SamplingMode = 'Sample based';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_X.InitialValue = '';
% Signal crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y = Simulink.Signal;
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y.RTWInfo.Alias = '';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y.Description = ...
  ['Frame: RT_SB_INS_Vel_ECEF_1, 9310754 (0x8e1222).' char(10) ...
   'Signal: Accuracy_INS_Vel_ECEF_Y.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y.Min = 0.0;
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y.Max = 255.0;
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y.DocUnits = '';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y.Dimensions = 1;
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y.Complexity = 'real';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y.SampleTime = -1;
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y.SamplingMode = 'Sample based';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Y.InitialValue = '';
% Signal crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z = Simulink.Signal;
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z.RTWInfo.Alias = '';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z.Description = ...
  ['Frame: RT_SB_INS_Vel_ECEF_1, 9310754 (0x8e1222).' char(10) ...
   'Signal: Accuracy_INS_Vel_ECEF_Z.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z.Min = 0.0;
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z.Max = 255.0;
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z.DocUnits = '';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z.Dimensions = 1;
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z.Complexity = 'real';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z.SampleTime = -1;
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z.SamplingMode = 'Sample based';
crt_PT_8e1222_Accuracy_INS_Vel_ECEF_Z.InitialValue = '';
% Signal crt_PT_8e1222_INS_Vel_ECEF_X
crt_PT_8e1222_INS_Vel_ECEF_X = Simulink.Signal;
crt_PT_8e1222_INS_Vel_ECEF_X.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1222_INS_Vel_ECEF_X.RTWInfo.Alias = '';
crt_PT_8e1222_INS_Vel_ECEF_X.Description = ...
  ['ECEF X velocity.  The ECEF X axis originates from the Earth centre, and the positive X axis intersects the Earth surface at zero degrees latittude and zero degrees longitude (the intersection of the equator and the prime meridian).' char(10) ...
   'Frame: RT_SB_INS_Vel_ECEF_1, 9310754 (0x8e1222).' char(10) ...
   'Signal: INS_Vel_ECEF_X.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8e1222_INS_Vel_ECEF_X.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8e1222_INS_Vel_ECEF_X.Min = -838.0;
crt_PT_8e1222_INS_Vel_ECEF_X.Max = 838.0;
crt_PT_8e1222_INS_Vel_ECEF_X.DocUnits = 'm/s';
crt_PT_8e1222_INS_Vel_ECEF_X.Dimensions = 1;
crt_PT_8e1222_INS_Vel_ECEF_X.Complexity = 'real';
crt_PT_8e1222_INS_Vel_ECEF_X.SampleTime = -1;
crt_PT_8e1222_INS_Vel_ECEF_X.SamplingMode = 'Sample based';
crt_PT_8e1222_INS_Vel_ECEF_X.InitialValue = '';

% Frame RT_SB_INS_Vel_NED_2, 9310498 (0x8e1122)
% Signal crt_PT_8e1122_Validity_INS_Vel_NED_D
crt_PT_8e1122_Validity_INS_Vel_NED_D = Simulink.Signal;
crt_PT_8e1122_Validity_INS_Vel_NED_D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1122_Validity_INS_Vel_NED_D.RTWInfo.Alias = '';
crt_PT_8e1122_Validity_INS_Vel_NED_D.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_INS_Vel_NED_2, 9310498 (0x8e1122).' char(10) ...
   'Signal: Validity_INS_Vel_NED_D.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1122_Validity_INS_Vel_NED_D.DataType = 'boolean';
crt_PT_8e1122_Validity_INS_Vel_NED_D.Min = 0.0;
crt_PT_8e1122_Validity_INS_Vel_NED_D.Max = 1.0;
crt_PT_8e1122_Validity_INS_Vel_NED_D.DocUnits = '';
crt_PT_8e1122_Validity_INS_Vel_NED_D.Dimensions = 1;
crt_PT_8e1122_Validity_INS_Vel_NED_D.Complexity = 'real';
crt_PT_8e1122_Validity_INS_Vel_NED_D.SampleTime = -1;
crt_PT_8e1122_Validity_INS_Vel_NED_D.SamplingMode = 'Sample based';
crt_PT_8e1122_Validity_INS_Vel_NED_D.InitialValue = '';
% Signal crt_PT_8e1122_Accuracy_INS_Vel_D
crt_PT_8e1122_Accuracy_INS_Vel_D = Simulink.Signal;
crt_PT_8e1122_Accuracy_INS_Vel_D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1122_Accuracy_INS_Vel_D.RTWInfo.Alias = '';
crt_PT_8e1122_Accuracy_INS_Vel_D.Description = ...
  ['Frame: RT_SB_INS_Vel_NED_2, 9310498 (0x8e1122).' char(10) ...
   'Signal: Accuracy_INS_Vel_D.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1122_Accuracy_INS_Vel_D.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e1122_Accuracy_INS_Vel_D.Min = 0.0;
crt_PT_8e1122_Accuracy_INS_Vel_D.Max = 255.0;
crt_PT_8e1122_Accuracy_INS_Vel_D.DocUnits = '';
crt_PT_8e1122_Accuracy_INS_Vel_D.Dimensions = 1;
crt_PT_8e1122_Accuracy_INS_Vel_D.Complexity = 'real';
crt_PT_8e1122_Accuracy_INS_Vel_D.SampleTime = -1;
crt_PT_8e1122_Accuracy_INS_Vel_D.SamplingMode = 'Sample based';
crt_PT_8e1122_Accuracy_INS_Vel_D.InitialValue = '';
% Signal crt_PT_8e1122_INS_Vel_NED_D
crt_PT_8e1122_INS_Vel_NED_D = Simulink.Signal;
crt_PT_8e1122_INS_Vel_NED_D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1122_INS_Vel_NED_D.RTWInfo.Alias = '';
crt_PT_8e1122_INS_Vel_NED_D.Description = ...
  ['VELNED D velocity.  This is the velocity vector directly downwards towards the Earth centre at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_INS_Vel_NED_2, 9310498 (0x8e1122).' char(10) ...
   'Signal: INS_Vel_NED_D.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8e1122_INS_Vel_NED_D.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8e1122_INS_Vel_NED_D.Min = -838.0;
crt_PT_8e1122_INS_Vel_NED_D.Max = 838.0;
crt_PT_8e1122_INS_Vel_NED_D.DocUnits = 'm/s';
crt_PT_8e1122_INS_Vel_NED_D.Dimensions = 1;
crt_PT_8e1122_INS_Vel_NED_D.Complexity = 'real';
crt_PT_8e1122_INS_Vel_NED_D.SampleTime = -1;
crt_PT_8e1122_INS_Vel_NED_D.SamplingMode = 'Sample based';
crt_PT_8e1122_INS_Vel_NED_D.InitialValue = '';

% Frame RT_SB_INS_Vel_NED_1, 9310242 (0x8e1022)
% Signal crt_PT_8e1022_Validity_INS_Vel_NED_N
crt_PT_8e1022_Validity_INS_Vel_NED_N = Simulink.Signal;
crt_PT_8e1022_Validity_INS_Vel_NED_N.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1022_Validity_INS_Vel_NED_N.RTWInfo.Alias = '';
crt_PT_8e1022_Validity_INS_Vel_NED_N.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_INS_Vel_NED_1, 9310242 (0x8e1022).' char(10) ...
   'Signal: Validity_INS_Vel_NED_N.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1022_Validity_INS_Vel_NED_N.DataType = 'boolean';
crt_PT_8e1022_Validity_INS_Vel_NED_N.Min = 0.0;
crt_PT_8e1022_Validity_INS_Vel_NED_N.Max = 1.0;
crt_PT_8e1022_Validity_INS_Vel_NED_N.DocUnits = '';
crt_PT_8e1022_Validity_INS_Vel_NED_N.Dimensions = 1;
crt_PT_8e1022_Validity_INS_Vel_NED_N.Complexity = 'real';
crt_PT_8e1022_Validity_INS_Vel_NED_N.SampleTime = -1;
crt_PT_8e1022_Validity_INS_Vel_NED_N.SamplingMode = 'Sample based';
crt_PT_8e1022_Validity_INS_Vel_NED_N.InitialValue = '';
% Signal crt_PT_8e1022_Validity_INS_Vel_NED_E
crt_PT_8e1022_Validity_INS_Vel_NED_E = Simulink.Signal;
crt_PT_8e1022_Validity_INS_Vel_NED_E.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1022_Validity_INS_Vel_NED_E.RTWInfo.Alias = '';
crt_PT_8e1022_Validity_INS_Vel_NED_E.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_INS_Vel_NED_1, 9310242 (0x8e1022).' char(10) ...
   'Signal: Validity_INS_Vel_NED_E.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1022_Validity_INS_Vel_NED_E.DataType = 'boolean';
crt_PT_8e1022_Validity_INS_Vel_NED_E.Min = 0.0;
crt_PT_8e1022_Validity_INS_Vel_NED_E.Max = 1.0;
crt_PT_8e1022_Validity_INS_Vel_NED_E.DocUnits = '';
crt_PT_8e1022_Validity_INS_Vel_NED_E.Dimensions = 1;
crt_PT_8e1022_Validity_INS_Vel_NED_E.Complexity = 'real';
crt_PT_8e1022_Validity_INS_Vel_NED_E.SampleTime = -1;
crt_PT_8e1022_Validity_INS_Vel_NED_E.SamplingMode = 'Sample based';
crt_PT_8e1022_Validity_INS_Vel_NED_E.InitialValue = '';
% Signal crt_PT_8e1022_Accuracy_INS_Vel_NE
crt_PT_8e1022_Accuracy_INS_Vel_NE = Simulink.Signal;
crt_PT_8e1022_Accuracy_INS_Vel_NE.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1022_Accuracy_INS_Vel_NE.RTWInfo.Alias = '';
crt_PT_8e1022_Accuracy_INS_Vel_NE.Description = ...
  ['Frame: RT_SB_INS_Vel_NED_1, 9310242 (0x8e1022).' char(10) ...
   'Signal: Accuracy_INS_Vel_NE.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1022_Accuracy_INS_Vel_NE.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e1022_Accuracy_INS_Vel_NE.Min = 0.0;
crt_PT_8e1022_Accuracy_INS_Vel_NE.Max = 255.0;
crt_PT_8e1022_Accuracy_INS_Vel_NE.DocUnits = '';
crt_PT_8e1022_Accuracy_INS_Vel_NE.Dimensions = 1;
crt_PT_8e1022_Accuracy_INS_Vel_NE.Complexity = 'real';
crt_PT_8e1022_Accuracy_INS_Vel_NE.SampleTime = -1;
crt_PT_8e1022_Accuracy_INS_Vel_NE.SamplingMode = 'Sample based';
crt_PT_8e1022_Accuracy_INS_Vel_NE.InitialValue = '';
% Signal crt_PT_8e1022_INS_Vel_NED_N
crt_PT_8e1022_INS_Vel_NED_N = Simulink.Signal;
crt_PT_8e1022_INS_Vel_NED_N.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1022_INS_Vel_NED_N.RTWInfo.Alias = '';
crt_PT_8e1022_INS_Vel_NED_N.Description = ...
  ['VELNED N velocity.  This is the velocity vector directly North at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_INS_Vel_NED_1, 9310242 (0x8e1022).' char(10) ...
   'Signal: INS_Vel_NED_N.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8e1022_INS_Vel_NED_N.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8e1022_INS_Vel_NED_N.Min = -838.0;
crt_PT_8e1022_INS_Vel_NED_N.Max = 838.0;
crt_PT_8e1022_INS_Vel_NED_N.DocUnits = 'm/s';
crt_PT_8e1022_INS_Vel_NED_N.Dimensions = 1;
crt_PT_8e1022_INS_Vel_NED_N.Complexity = 'real';
crt_PT_8e1022_INS_Vel_NED_N.SampleTime = -1;
crt_PT_8e1022_INS_Vel_NED_N.SamplingMode = 'Sample based';
crt_PT_8e1022_INS_Vel_NED_N.InitialValue = '';
% Signal crt_PT_8e1022_INS_Vel_NED_E
crt_PT_8e1022_INS_Vel_NED_E = Simulink.Signal;
crt_PT_8e1022_INS_Vel_NED_E.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1022_INS_Vel_NED_E.RTWInfo.Alias = '';
crt_PT_8e1022_INS_Vel_NED_E.Description = ...
  ['VELNED E velocity.  This is the velocity vector directly East at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_INS_Vel_NED_1, 9310242 (0x8e1022).' char(10) ...
   'Signal: INS_Vel_NED_E.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8e1022_INS_Vel_NED_E.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8e1022_INS_Vel_NED_E.Min = -838.0;
crt_PT_8e1022_INS_Vel_NED_E.Max = 838.0;
crt_PT_8e1022_INS_Vel_NED_E.DocUnits = 'm/s';
crt_PT_8e1022_INS_Vel_NED_E.Dimensions = 1;
crt_PT_8e1022_INS_Vel_NED_E.Complexity = 'real';
crt_PT_8e1022_INS_Vel_NED_E.SampleTime = -1;
crt_PT_8e1022_INS_Vel_NED_E.SamplingMode = 'Sample based';
crt_PT_8e1022_INS_Vel_NED_E.InitialValue = '';

% Frame RT_SB_INS_Pos_ECEF_2, 9307426 (0x8e0522)
% Signal crt_PT_8e0522_INS_Pos_ECEF_Y
crt_PT_8e0522_INS_Pos_ECEF_Y = Simulink.Signal;
crt_PT_8e0522_INS_Pos_ECEF_Y.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0522_INS_Pos_ECEF_Y.RTWInfo.Alias = '';
crt_PT_8e0522_INS_Pos_ECEF_Y.Description = ...
  ['ECEF Y position.  The ECEF Y axis originates from the Earth centre, and the positive Y axis intersects the Earth surface at zero degrees latittude and 90 degrees longitude.' char(10) ...
   'Frame: RT_SB_INS_Pos_ECEF_2, 9307426 (0x8e0522).' char(10) ...
   'Signal: INS_Pos_ECEF_Y.' char(10) ...
   'Range (world values): -1.0E7 ... 1.0E7 [m].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8e0522_INS_Pos_ECEF_Y.DataType = 'fixdt(1, 32, 0.01, 0.0)';
crt_PT_8e0522_INS_Pos_ECEF_Y.Min = -1.0E7;
crt_PT_8e0522_INS_Pos_ECEF_Y.Max = 1.0E7;
crt_PT_8e0522_INS_Pos_ECEF_Y.DocUnits = 'm';
crt_PT_8e0522_INS_Pos_ECEF_Y.Dimensions = 1;
crt_PT_8e0522_INS_Pos_ECEF_Y.Complexity = 'real';
crt_PT_8e0522_INS_Pos_ECEF_Y.SampleTime = -1;
crt_PT_8e0522_INS_Pos_ECEF_Y.SamplingMode = 'Sample based';
crt_PT_8e0522_INS_Pos_ECEF_Y.InitialValue = '';
% Signal crt_PT_8e0522_INS_Pos_ECEF_Z
crt_PT_8e0522_INS_Pos_ECEF_Z = Simulink.Signal;
crt_PT_8e0522_INS_Pos_ECEF_Z.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0522_INS_Pos_ECEF_Z.RTWInfo.Alias = '';
crt_PT_8e0522_INS_Pos_ECEF_Z.Description = ...
  ['ECEF Z position.  The ECEF Z axis originates from the Earth centre, and the positive Z axis intersects the Earth surface at the North Pole.' char(10) ...
   'Frame: RT_SB_INS_Pos_ECEF_2, 9307426 (0x8e0522).' char(10) ...
   'Signal: INS_Pos_ECEF_Z.' char(10) ...
   'Range (world values): -1.0E7 ... 1.0E7 [m].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8e0522_INS_Pos_ECEF_Z.DataType = 'fixdt(1, 32, 0.01, 0.0)';
crt_PT_8e0522_INS_Pos_ECEF_Z.Min = -1.0E7;
crt_PT_8e0522_INS_Pos_ECEF_Z.Max = 1.0E7;
crt_PT_8e0522_INS_Pos_ECEF_Z.DocUnits = 'm';
crt_PT_8e0522_INS_Pos_ECEF_Z.Dimensions = 1;
crt_PT_8e0522_INS_Pos_ECEF_Z.Complexity = 'real';
crt_PT_8e0522_INS_Pos_ECEF_Z.SampleTime = -1;
crt_PT_8e0522_INS_Pos_ECEF_Z.SamplingMode = 'Sample based';
crt_PT_8e0522_INS_Pos_ECEF_Z.InitialValue = '';

% Frame RT_SB_INS_Pos_ECEF_1, 9307170 (0x8e0422)
% Signal crt_PT_8e0422_Validity_INS_Pos_ECEF_X
crt_PT_8e0422_Validity_INS_Pos_ECEF_X = Simulink.Signal;
crt_PT_8e0422_Validity_INS_Pos_ECEF_X.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0422_Validity_INS_Pos_ECEF_X.RTWInfo.Alias = '';
crt_PT_8e0422_Validity_INS_Pos_ECEF_X.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_INS_Pos_ECEF_1, 9307170 (0x8e0422).' char(10) ...
   'Signal: Validity_INS_Pos_ECEF_X.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0422_Validity_INS_Pos_ECEF_X.DataType = 'boolean';
crt_PT_8e0422_Validity_INS_Pos_ECEF_X.Min = 0.0;
crt_PT_8e0422_Validity_INS_Pos_ECEF_X.Max = 1.0;
crt_PT_8e0422_Validity_INS_Pos_ECEF_X.DocUnits = '';
crt_PT_8e0422_Validity_INS_Pos_ECEF_X.Dimensions = 1;
crt_PT_8e0422_Validity_INS_Pos_ECEF_X.Complexity = 'real';
crt_PT_8e0422_Validity_INS_Pos_ECEF_X.SampleTime = -1;
crt_PT_8e0422_Validity_INS_Pos_ECEF_X.SamplingMode = 'Sample based';
crt_PT_8e0422_Validity_INS_Pos_ECEF_X.InitialValue = '';
% Signal crt_PT_8e0422_Validity_INS_Pos_ECEF_Y
crt_PT_8e0422_Validity_INS_Pos_ECEF_Y = Simulink.Signal;
crt_PT_8e0422_Validity_INS_Pos_ECEF_Y.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0422_Validity_INS_Pos_ECEF_Y.RTWInfo.Alias = '';
crt_PT_8e0422_Validity_INS_Pos_ECEF_Y.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_INS_Pos_ECEF_1, 9307170 (0x8e0422).' char(10) ...
   'Signal: Validity_INS_Pos_ECEF_Y.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0422_Validity_INS_Pos_ECEF_Y.DataType = 'boolean';
crt_PT_8e0422_Validity_INS_Pos_ECEF_Y.Min = 0.0;
crt_PT_8e0422_Validity_INS_Pos_ECEF_Y.Max = 1.0;
crt_PT_8e0422_Validity_INS_Pos_ECEF_Y.DocUnits = '';
crt_PT_8e0422_Validity_INS_Pos_ECEF_Y.Dimensions = 1;
crt_PT_8e0422_Validity_INS_Pos_ECEF_Y.Complexity = 'real';
crt_PT_8e0422_Validity_INS_Pos_ECEF_Y.SampleTime = -1;
crt_PT_8e0422_Validity_INS_Pos_ECEF_Y.SamplingMode = 'Sample based';
crt_PT_8e0422_Validity_INS_Pos_ECEF_Y.InitialValue = '';
% Signal crt_PT_8e0422_Validity_INS_Pos_ECEF_Z
crt_PT_8e0422_Validity_INS_Pos_ECEF_Z = Simulink.Signal;
crt_PT_8e0422_Validity_INS_Pos_ECEF_Z.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0422_Validity_INS_Pos_ECEF_Z.RTWInfo.Alias = '';
crt_PT_8e0422_Validity_INS_Pos_ECEF_Z.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_INS_Pos_ECEF_1, 9307170 (0x8e0422).' char(10) ...
   'Signal: Validity_INS_Pos_ECEF_Z.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0422_Validity_INS_Pos_ECEF_Z.DataType = 'boolean';
crt_PT_8e0422_Validity_INS_Pos_ECEF_Z.Min = 0.0;
crt_PT_8e0422_Validity_INS_Pos_ECEF_Z.Max = 1.0;
crt_PT_8e0422_Validity_INS_Pos_ECEF_Z.DocUnits = '';
crt_PT_8e0422_Validity_INS_Pos_ECEF_Z.Dimensions = 1;
crt_PT_8e0422_Validity_INS_Pos_ECEF_Z.Complexity = 'real';
crt_PT_8e0422_Validity_INS_Pos_ECEF_Z.SampleTime = -1;
crt_PT_8e0422_Validity_INS_Pos_ECEF_Z.SamplingMode = 'Sample based';
crt_PT_8e0422_Validity_INS_Pos_ECEF_Z.InitialValue = '';
% Signal crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X = Simulink.Signal;
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X.RTWInfo.Alias = '';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_INS_Pos_ECEF_1, 9307170 (0x8e0422).' char(10) ...
   'Signal: Accuracy_INS_Pos_ECEF_X.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X.Min = 0.0;
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X.Max = 255.0;
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X.DocUnits = '';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X.Dimensions = 1;
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X.Complexity = 'real';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X.SampleTime = -1;
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X.SamplingMode = 'Sample based';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_X.InitialValue = '';
% Signal crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y = Simulink.Signal;
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y.RTWInfo.Alias = '';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_INS_Pos_ECEF_1, 9307170 (0x8e0422).' char(10) ...
   'Signal: Accuracy_INS_Pos_ECEF_Y.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y.Min = 0.0;
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y.Max = 255.0;
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y.DocUnits = '';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y.Dimensions = 1;
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y.Complexity = 'real';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y.SampleTime = -1;
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y.SamplingMode = 'Sample based';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Y.InitialValue = '';
% Signal crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z = Simulink.Signal;
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z.RTWInfo.Alias = '';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_INS_Pos_ECEF_1, 9307170 (0x8e0422).' char(10) ...
   'Signal: Accuracy_INS_Pos_ECEF_Z.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z.Min = 0.0;
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z.Max = 255.0;
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z.DocUnits = '';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z.Dimensions = 1;
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z.Complexity = 'real';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z.SampleTime = -1;
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z.SamplingMode = 'Sample based';
crt_PT_8e0422_Accuracy_INS_Pos_ECEF_Z.InitialValue = '';
% Signal crt_PT_8e0422_INS_Pos_ECEF_X
crt_PT_8e0422_INS_Pos_ECEF_X = Simulink.Signal;
crt_PT_8e0422_INS_Pos_ECEF_X.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0422_INS_Pos_ECEF_X.RTWInfo.Alias = '';
crt_PT_8e0422_INS_Pos_ECEF_X.Description = ...
  ['ECEF X position.  The ECEF X axis originates from the Earth centre, and the positive X axis intersects the Earth surface at zero degrees latittude and zero degrees longitude (the intersection of the equator and the prime meridian).' char(10) ...
   'Frame: RT_SB_INS_Pos_ECEF_1, 9307170 (0x8e0422).' char(10) ...
   'Signal: INS_Pos_ECEF_X.' char(10) ...
   'Range (world values): -1.0E7 ... 1.0E7 [m].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8e0422_INS_Pos_ECEF_X.DataType = 'fixdt(1, 32, 0.01, 0.0)';
crt_PT_8e0422_INS_Pos_ECEF_X.Min = -1.0E7;
crt_PT_8e0422_INS_Pos_ECEF_X.Max = 1.0E7;
crt_PT_8e0422_INS_Pos_ECEF_X.DocUnits = 'm';
crt_PT_8e0422_INS_Pos_ECEF_X.Dimensions = 1;
crt_PT_8e0422_INS_Pos_ECEF_X.Complexity = 'real';
crt_PT_8e0422_INS_Pos_ECEF_X.SampleTime = -1;
crt_PT_8e0422_INS_Pos_ECEF_X.SamplingMode = 'Sample based';
crt_PT_8e0422_INS_Pos_ECEF_X.InitialValue = '';

% Frame RT_SB_INS_Pos_LLH_2, 9306914 (0x8e0322)
% Signal crt_PT_8e0322_INS_Pos_LLH_Longitude
crt_PT_8e0322_INS_Pos_LLH_Longitude = Simulink.Signal;
crt_PT_8e0322_INS_Pos_LLH_Longitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0322_INS_Pos_LLH_Longitude.RTWInfo.Alias = '';
crt_PT_8e0322_INS_Pos_LLH_Longitude.Description = ...
  ['Frame: RT_SB_INS_Pos_LLH_2, 9306914 (0x8e0322).' char(10) ...
   'Signal: INS_Pos_LLH_Longitude.' char(10) ...
   'Range (world values): -180.0 ... 180.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 1.0E-7*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8e0322_INS_Pos_LLH_Longitude.DataType = 'fixdt(1, 32, 1.0E-7, 0.0)';
crt_PT_8e0322_INS_Pos_LLH_Longitude.Min = -180.0;
crt_PT_8e0322_INS_Pos_LLH_Longitude.Max = 180.0;
crt_PT_8e0322_INS_Pos_LLH_Longitude.DocUnits = 'degrees';
crt_PT_8e0322_INS_Pos_LLH_Longitude.Dimensions = 1;
crt_PT_8e0322_INS_Pos_LLH_Longitude.Complexity = 'real';
crt_PT_8e0322_INS_Pos_LLH_Longitude.SampleTime = -1;
crt_PT_8e0322_INS_Pos_LLH_Longitude.SamplingMode = 'Sample based';
crt_PT_8e0322_INS_Pos_LLH_Longitude.InitialValue = '';
% Signal crt_PT_8e0322_INS_Pos_LLH_Altitude
crt_PT_8e0322_INS_Pos_LLH_Altitude = Simulink.Signal;
crt_PT_8e0322_INS_Pos_LLH_Altitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0322_INS_Pos_LLH_Altitude.RTWInfo.Alias = '';
crt_PT_8e0322_INS_Pos_LLH_Altitude.Description = ...
  ['Frame: RT_SB_INS_Pos_LLH_2, 9306914 (0x8e0322).' char(10) ...
   'Signal: INS_Pos_LLH_Altitude.' char(10) ...
   'Range (world values): -1000.0 ... 100000.0 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8e0322_INS_Pos_LLH_Altitude.DataType = 'fixdt(1, 32, 0.001, 0.0)';
crt_PT_8e0322_INS_Pos_LLH_Altitude.Min = -1000.0;
crt_PT_8e0322_INS_Pos_LLH_Altitude.Max = 100000.0;
crt_PT_8e0322_INS_Pos_LLH_Altitude.DocUnits = 'm';
crt_PT_8e0322_INS_Pos_LLH_Altitude.Dimensions = 1;
crt_PT_8e0322_INS_Pos_LLH_Altitude.Complexity = 'real';
crt_PT_8e0322_INS_Pos_LLH_Altitude.SampleTime = -1;
crt_PT_8e0322_INS_Pos_LLH_Altitude.SamplingMode = 'Sample based';
crt_PT_8e0322_INS_Pos_LLH_Altitude.InitialValue = '';

% Frame RT_SB_INS_Pos_LLH_1, 9306658 (0x8e0222)
% Signal crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude
crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude = Simulink.Signal;
crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude.RTWInfo.Alias = '';
crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_INS_Pos_LLH_1, 9306658 (0x8e0222).' char(10) ...
   'Signal: Validity_INS_Pos_LLH_Latitude.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude.DataType = 'boolean';
crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude.Min = 0.0;
crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude.Max = 1.0;
crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude.DocUnits = '';
crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude.Dimensions = 1;
crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude.Complexity = 'real';
crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude.SampleTime = -1;
crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude.SamplingMode = 'Sample based';
crt_PT_8e0222_Validity_INS_Pos_LLH_Latitude.InitialValue = '';
% Signal crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude
crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude = Simulink.Signal;
crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude.RTWInfo.Alias = '';
crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_INS_Pos_LLH_1, 9306658 (0x8e0222).' char(10) ...
   'Signal: Validity_INS_Pos_LLH_Longitude.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude.DataType = 'boolean';
crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude.Min = 0.0;
crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude.Max = 1.0;
crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude.DocUnits = '';
crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude.Dimensions = 1;
crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude.Complexity = 'real';
crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude.SampleTime = -1;
crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude.SamplingMode = 'Sample based';
crt_PT_8e0222_Validity_INS_Pos_LLH_Longitude.InitialValue = '';
% Signal crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude
crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude = Simulink.Signal;
crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude.RTWInfo.Alias = '';
crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_INS_Pos_LLH_1, 9306658 (0x8e0222).' char(10) ...
   'Signal: Validity_INS_Pos_LLH_Altitude.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude.DataType = 'boolean';
crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude.Min = 0.0;
crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude.Max = 1.0;
crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude.DocUnits = '';
crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude.Dimensions = 1;
crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude.Complexity = 'real';
crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude.SampleTime = -1;
crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude.SamplingMode = 'Sample based';
crt_PT_8e0222_Validity_INS_Pos_LLH_Altitude.InitialValue = '';
% Signal crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude = Simulink.Signal;
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude.RTWInfo.Alias = '';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude.Description = ...
  ['This accuracy value applies to both 2D and 3D GPS speed.' char(10) ...
   'Frame: RT_SB_INS_Pos_LLH_1, 9306658 (0x8e0222).' char(10) ...
   'Signal: Accuracy_INS_Pos_LLH_Latitude.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude.Min = 0.0;
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude.Max = 255.0;
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude.DocUnits = '';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude.Dimensions = 1;
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude.Complexity = 'real';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude.SampleTime = -1;
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude.SamplingMode = 'Sample based';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Latitude.InitialValue = '';
% Signal crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude = Simulink.Signal;
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude.RTWInfo.Alias = '';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude.Description = ...
  ['This accuracy value applies to both 2D and 3D GPS speed.' char(10) ...
   'Frame: RT_SB_INS_Pos_LLH_1, 9306658 (0x8e0222).' char(10) ...
   'Signal: Accuracy_INS_Pos_LLH_Longitude.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude.Min = 0.0;
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude.Max = 255.0;
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude.DocUnits = '';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude.Dimensions = 1;
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude.Complexity = 'real';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude.SampleTime = -1;
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude.SamplingMode = 'Sample based';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Longitude.InitialValue = '';
% Signal crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude = Simulink.Signal;
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude.RTWInfo.Alias = '';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude.Description = ...
  ['This accuracy value applies to both 2D and 3D GPS speed.' char(10) ...
   'Frame: RT_SB_INS_Pos_LLH_1, 9306658 (0x8e0222).' char(10) ...
   'Signal: Accuracy_INS_Pos_LLH_Altitude.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude.Min = 0.0;
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude.Max = 255.0;
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude.DocUnits = '';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude.Dimensions = 1;
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude.Complexity = 'real';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude.SampleTime = -1;
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude.SamplingMode = 'Sample based';
crt_PT_8e0222_Accuracy_INS_Pos_LLH_Altitude.InitialValue = '';
% Signal crt_PT_8e0222_INS_Pos_LLH_Latitude
crt_PT_8e0222_INS_Pos_LLH_Latitude = Simulink.Signal;
crt_PT_8e0222_INS_Pos_LLH_Latitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0222_INS_Pos_LLH_Latitude.RTWInfo.Alias = '';
crt_PT_8e0222_INS_Pos_LLH_Latitude.Description = ...
  ['Frame: RT_SB_INS_Pos_LLH_1, 9306658 (0x8e0222).' char(10) ...
   'Signal: INS_Pos_LLH_Latitude.' char(10) ...
   'Range (world values): -90.0 ... 90.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 1.0E-7*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8e0222_INS_Pos_LLH_Latitude.DataType = 'fixdt(1, 32, 1.0E-7, 0.0)';
crt_PT_8e0222_INS_Pos_LLH_Latitude.Min = -90.0;
crt_PT_8e0222_INS_Pos_LLH_Latitude.Max = 90.0;
crt_PT_8e0222_INS_Pos_LLH_Latitude.DocUnits = 'degrees';
crt_PT_8e0222_INS_Pos_LLH_Latitude.Dimensions = 1;
crt_PT_8e0222_INS_Pos_LLH_Latitude.Complexity = 'real';
crt_PT_8e0222_INS_Pos_LLH_Latitude.SampleTime = -1;
crt_PT_8e0222_INS_Pos_LLH_Latitude.SamplingMode = 'Sample based';
crt_PT_8e0222_INS_Pos_LLH_Latitude.InitialValue = '';

% Frame RT_SB_INS_Heading_Gradient_2, 9311522 (0x8e1522)
% Signal crt_PT_8e1522_Validity_INS_Heading
crt_PT_8e1522_Validity_INS_Heading = Simulink.Signal;
crt_PT_8e1522_Validity_INS_Heading.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1522_Validity_INS_Heading.RTWInfo.Alias = '';
crt_PT_8e1522_Validity_INS_Heading.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_INS_Heading_Gradient_2, 9311522 (0x8e1522).' char(10) ...
   'Signal: Validity_INS_Heading.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1522_Validity_INS_Heading.DataType = 'boolean';
crt_PT_8e1522_Validity_INS_Heading.Min = 0.0;
crt_PT_8e1522_Validity_INS_Heading.Max = 1.0;
crt_PT_8e1522_Validity_INS_Heading.DocUnits = '';
crt_PT_8e1522_Validity_INS_Heading.Dimensions = 1;
crt_PT_8e1522_Validity_INS_Heading.Complexity = 'real';
crt_PT_8e1522_Validity_INS_Heading.SampleTime = -1;
crt_PT_8e1522_Validity_INS_Heading.SamplingMode = 'Sample based';
crt_PT_8e1522_Validity_INS_Heading.InitialValue = '';
% Signal crt_PT_8e1522_Validity_INS_Gradient
crt_PT_8e1522_Validity_INS_Gradient = Simulink.Signal;
crt_PT_8e1522_Validity_INS_Gradient.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1522_Validity_INS_Gradient.RTWInfo.Alias = '';
crt_PT_8e1522_Validity_INS_Gradient.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_INS_Heading_Gradient_2, 9311522 (0x8e1522).' char(10) ...
   'Signal: Validity_INS_Gradient.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1522_Validity_INS_Gradient.DataType = 'boolean';
crt_PT_8e1522_Validity_INS_Gradient.Min = 0.0;
crt_PT_8e1522_Validity_INS_Gradient.Max = 1.0;
crt_PT_8e1522_Validity_INS_Gradient.DocUnits = '';
crt_PT_8e1522_Validity_INS_Gradient.Dimensions = 1;
crt_PT_8e1522_Validity_INS_Gradient.Complexity = 'real';
crt_PT_8e1522_Validity_INS_Gradient.SampleTime = -1;
crt_PT_8e1522_Validity_INS_Gradient.SamplingMode = 'Sample based';
crt_PT_8e1522_Validity_INS_Gradient.InitialValue = '';
% Signal crt_PT_8e1522_Accuracy_INS_Heading
crt_PT_8e1522_Accuracy_INS_Heading = Simulink.Signal;
crt_PT_8e1522_Accuracy_INS_Heading.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1522_Accuracy_INS_Heading.RTWInfo.Alias = '';
crt_PT_8e1522_Accuracy_INS_Heading.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_INS_Heading_Gradient_2, 9311522 (0x8e1522).' char(10) ...
   'Signal: Accuracy_INS_Heading.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1522_Accuracy_INS_Heading.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e1522_Accuracy_INS_Heading.Min = 0.0;
crt_PT_8e1522_Accuracy_INS_Heading.Max = 255.0;
crt_PT_8e1522_Accuracy_INS_Heading.DocUnits = '';
crt_PT_8e1522_Accuracy_INS_Heading.Dimensions = 1;
crt_PT_8e1522_Accuracy_INS_Heading.Complexity = 'real';
crt_PT_8e1522_Accuracy_INS_Heading.SampleTime = -1;
crt_PT_8e1522_Accuracy_INS_Heading.SamplingMode = 'Sample based';
crt_PT_8e1522_Accuracy_INS_Heading.InitialValue = '';
% Signal crt_PT_8e1522_INS_Heading_2
crt_PT_8e1522_INS_Heading_2 = Simulink.Signal;
crt_PT_8e1522_INS_Heading_2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1522_INS_Heading_2.RTWInfo.Alias = '';
crt_PT_8e1522_INS_Heading_2.Description = ...
  ['This is GPS heading in the range 0 - 360., the direction that the vehicle is travelling in the local horizontal plane.' char(10) ...
   'Frame: RT_SB_INS_Heading_Gradient_2, 9311522 (0x8e1522).' char(10) ...
   'Signal: INS_Heading_2.' char(10) ...
   'Range (world values): 0.0 ... 360.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8e1522_INS_Heading_2.DataType = 'fixdt(0, 16, 0.01, 0.0)';
crt_PT_8e1522_INS_Heading_2.Min = 0.0;
crt_PT_8e1522_INS_Heading_2.Max = 360.0;
crt_PT_8e1522_INS_Heading_2.DocUnits = 'degrees';
crt_PT_8e1522_INS_Heading_2.Dimensions = 1;
crt_PT_8e1522_INS_Heading_2.Complexity = 'real';
crt_PT_8e1522_INS_Heading_2.SampleTime = -1;
crt_PT_8e1522_INS_Heading_2.SamplingMode = 'Sample based';
crt_PT_8e1522_INS_Heading_2.InitialValue = '';
% Signal crt_PT_8e1522_Accuracy_INS_Gradient
crt_PT_8e1522_Accuracy_INS_Gradient = Simulink.Signal;
crt_PT_8e1522_Accuracy_INS_Gradient.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1522_Accuracy_INS_Gradient.RTWInfo.Alias = '';
crt_PT_8e1522_Accuracy_INS_Gradient.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_INS_Heading_Gradient_2, 9311522 (0x8e1522).' char(10) ...
   'Signal: Accuracy_INS_Gradient.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1522_Accuracy_INS_Gradient.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e1522_Accuracy_INS_Gradient.Min = 0.0;
crt_PT_8e1522_Accuracy_INS_Gradient.Max = 255.0;
crt_PT_8e1522_Accuracy_INS_Gradient.DocUnits = '';
crt_PT_8e1522_Accuracy_INS_Gradient.Dimensions = 1;
crt_PT_8e1522_Accuracy_INS_Gradient.Complexity = 'real';
crt_PT_8e1522_Accuracy_INS_Gradient.SampleTime = -1;
crt_PT_8e1522_Accuracy_INS_Gradient.SamplingMode = 'Sample based';
crt_PT_8e1522_Accuracy_INS_Gradient.InitialValue = '';
% Signal crt_PT_8e1522_INS_Gradient
crt_PT_8e1522_INS_Gradient = Simulink.Signal;
crt_PT_8e1522_INS_Gradient.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1522_INS_Gradient.RTWInfo.Alias = '';
crt_PT_8e1522_INS_Gradient.Description = ...
  ['This is GPS gradient, i.e. the vertical direction that the vehicle is travelling, NOT pointing (pitch).' char(10) ...
   'Frame: RT_SB_INS_Heading_Gradient_2, 9311522 (0x8e1522).' char(10) ...
   'Signal: INS_Gradient.' char(10) ...
   'Range (world values): -90.0 ... 90.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8e1522_INS_Gradient.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8e1522_INS_Gradient.Min = -90.0;
crt_PT_8e1522_INS_Gradient.Max = 90.0;
crt_PT_8e1522_INS_Gradient.DocUnits = 'degrees';
crt_PT_8e1522_INS_Gradient.Dimensions = 1;
crt_PT_8e1522_INS_Gradient.Complexity = 'real';
crt_PT_8e1522_INS_Gradient.SampleTime = -1;
crt_PT_8e1522_INS_Gradient.SamplingMode = 'Sample based';
crt_PT_8e1522_INS_Gradient.InitialValue = '';

% Frame RT_SB_INS_Heading_Gradient, 9311266 (0x8e1422)
% Signal crt_PT_8e1422_Validity_INS_Heading
crt_PT_8e1422_Validity_INS_Heading = Simulink.Signal;
crt_PT_8e1422_Validity_INS_Heading.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1422_Validity_INS_Heading.RTWInfo.Alias = '';
crt_PT_8e1422_Validity_INS_Heading.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_INS_Heading_Gradient, 9311266 (0x8e1422).' char(10) ...
   'Signal: Validity_INS_Heading.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1422_Validity_INS_Heading.DataType = 'boolean';
crt_PT_8e1422_Validity_INS_Heading.Min = 0.0;
crt_PT_8e1422_Validity_INS_Heading.Max = 1.0;
crt_PT_8e1422_Validity_INS_Heading.DocUnits = '';
crt_PT_8e1422_Validity_INS_Heading.Dimensions = 1;
crt_PT_8e1422_Validity_INS_Heading.Complexity = 'real';
crt_PT_8e1422_Validity_INS_Heading.SampleTime = -1;
crt_PT_8e1422_Validity_INS_Heading.SamplingMode = 'Sample based';
crt_PT_8e1422_Validity_INS_Heading.InitialValue = '';
% Signal crt_PT_8e1422_Validity_INS_Gradient
crt_PT_8e1422_Validity_INS_Gradient = Simulink.Signal;
crt_PT_8e1422_Validity_INS_Gradient.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1422_Validity_INS_Gradient.RTWInfo.Alias = '';
crt_PT_8e1422_Validity_INS_Gradient.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_INS_Heading_Gradient, 9311266 (0x8e1422).' char(10) ...
   'Signal: Validity_INS_Gradient.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1422_Validity_INS_Gradient.DataType = 'boolean';
crt_PT_8e1422_Validity_INS_Gradient.Min = 0.0;
crt_PT_8e1422_Validity_INS_Gradient.Max = 1.0;
crt_PT_8e1422_Validity_INS_Gradient.DocUnits = '';
crt_PT_8e1422_Validity_INS_Gradient.Dimensions = 1;
crt_PT_8e1422_Validity_INS_Gradient.Complexity = 'real';
crt_PT_8e1422_Validity_INS_Gradient.SampleTime = -1;
crt_PT_8e1422_Validity_INS_Gradient.SamplingMode = 'Sample based';
crt_PT_8e1422_Validity_INS_Gradient.InitialValue = '';
% Signal crt_PT_8e1422_Accuracy_INS_Heading
crt_PT_8e1422_Accuracy_INS_Heading = Simulink.Signal;
crt_PT_8e1422_Accuracy_INS_Heading.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1422_Accuracy_INS_Heading.RTWInfo.Alias = '';
crt_PT_8e1422_Accuracy_INS_Heading.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_INS_Heading_Gradient, 9311266 (0x8e1422).' char(10) ...
   'Signal: Accuracy_INS_Heading.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1422_Accuracy_INS_Heading.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e1422_Accuracy_INS_Heading.Min = 0.0;
crt_PT_8e1422_Accuracy_INS_Heading.Max = 255.0;
crt_PT_8e1422_Accuracy_INS_Heading.DocUnits = '';
crt_PT_8e1422_Accuracy_INS_Heading.Dimensions = 1;
crt_PT_8e1422_Accuracy_INS_Heading.Complexity = 'real';
crt_PT_8e1422_Accuracy_INS_Heading.SampleTime = -1;
crt_PT_8e1422_Accuracy_INS_Heading.SamplingMode = 'Sample based';
crt_PT_8e1422_Accuracy_INS_Heading.InitialValue = '';
% Signal crt_PT_8e1422_INS_Heading
crt_PT_8e1422_INS_Heading = Simulink.Signal;
crt_PT_8e1422_INS_Heading.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1422_INS_Heading.RTWInfo.Alias = '';
crt_PT_8e1422_INS_Heading.Description = ...
  ['This is GPS heading, the direction that the vehicle is travelling in the local horizontal plane.' char(10) ...
   'Frame: RT_SB_INS_Heading_Gradient, 9311266 (0x8e1422).' char(10) ...
   'Signal: INS_Heading.' char(10) ...
   'Range (world values): -180.0 ... 180.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8e1422_INS_Heading.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8e1422_INS_Heading.Min = -180.0;
crt_PT_8e1422_INS_Heading.Max = 180.0;
crt_PT_8e1422_INS_Heading.DocUnits = 'degrees';
crt_PT_8e1422_INS_Heading.Dimensions = 1;
crt_PT_8e1422_INS_Heading.Complexity = 'real';
crt_PT_8e1422_INS_Heading.SampleTime = -1;
crt_PT_8e1422_INS_Heading.SamplingMode = 'Sample based';
crt_PT_8e1422_INS_Heading.InitialValue = '';
% Signal crt_PT_8e1422_Accuracy_INS_Gradient
crt_PT_8e1422_Accuracy_INS_Gradient = Simulink.Signal;
crt_PT_8e1422_Accuracy_INS_Gradient.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1422_Accuracy_INS_Gradient.RTWInfo.Alias = '';
crt_PT_8e1422_Accuracy_INS_Gradient.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_INS_Heading_Gradient, 9311266 (0x8e1422).' char(10) ...
   'Signal: Accuracy_INS_Gradient.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e1422_Accuracy_INS_Gradient.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e1422_Accuracy_INS_Gradient.Min = 0.0;
crt_PT_8e1422_Accuracy_INS_Gradient.Max = 255.0;
crt_PT_8e1422_Accuracy_INS_Gradient.DocUnits = '';
crt_PT_8e1422_Accuracy_INS_Gradient.Dimensions = 1;
crt_PT_8e1422_Accuracy_INS_Gradient.Complexity = 'real';
crt_PT_8e1422_Accuracy_INS_Gradient.SampleTime = -1;
crt_PT_8e1422_Accuracy_INS_Gradient.SamplingMode = 'Sample based';
crt_PT_8e1422_Accuracy_INS_Gradient.InitialValue = '';
% Signal crt_PT_8e1422_INS_Gradient
crt_PT_8e1422_INS_Gradient = Simulink.Signal;
crt_PT_8e1422_INS_Gradient.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e1422_INS_Gradient.RTWInfo.Alias = '';
crt_PT_8e1422_INS_Gradient.Description = ...
  ['This is GPS gradient, i.e. the vertical direction that the vehicle is travelling, NOT pointing (pitch).' char(10) ...
   'Frame: RT_SB_INS_Heading_Gradient, 9311266 (0x8e1422).' char(10) ...
   'Signal: INS_Gradient.' char(10) ...
   'Range (world values): -90.0 ... 90.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8e1422_INS_Gradient.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8e1422_INS_Gradient.Min = -90.0;
crt_PT_8e1422_INS_Gradient.Max = 90.0;
crt_PT_8e1422_INS_Gradient.DocUnits = 'degrees';
crt_PT_8e1422_INS_Gradient.Dimensions = 1;
crt_PT_8e1422_INS_Gradient.Complexity = 'real';
crt_PT_8e1422_INS_Gradient.SampleTime = -1;
crt_PT_8e1422_INS_Gradient.SamplingMode = 'Sample based';
crt_PT_8e1422_INS_Gradient.InitialValue = '';

% Frame RT_SB_INS_Status, 9306146 (0x8e0022)
% Signal crt_PT_8e0022_INS_Status
crt_PT_8e0022_INS_Status = Simulink.Signal;
crt_PT_8e0022_INS_Status.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0022_INS_Status.RTWInfo.Alias = '';
crt_PT_8e0022_INS_Status.Description = ...
  ['Frame: RT_SB_INS_Status, 9306146 (0x8e0022).' char(10) ...
   'Signal: INS_Status.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0022_INS_Status.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e0022_INS_Status.Min = 0.0;
crt_PT_8e0022_INS_Status.Max = 255.0;
crt_PT_8e0022_INS_Status.DocUnits = '';
crt_PT_8e0022_INS_Status.Dimensions = 1;
crt_PT_8e0022_INS_Status.Complexity = 'real';
crt_PT_8e0022_INS_Status.SampleTime = -1;
crt_PT_8e0022_INS_Status.SamplingMode = 'Sample based';
crt_PT_8e0022_INS_Status.InitialValue = '';

% Frame RT_SB_INS_Attitude, 9306402 (0x8e0122)
% Signal crt_PT_8e0122_Validity_Yaw
crt_PT_8e0122_Validity_Yaw = Simulink.Signal;
crt_PT_8e0122_Validity_Yaw.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0122_Validity_Yaw.RTWInfo.Alias = '';
crt_PT_8e0122_Validity_Yaw.Description = ...
  ['Frame: RT_SB_INS_Attitude, 9306402 (0x8e0122).' char(10) ...
   'Signal: Validity_Yaw.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0122_Validity_Yaw.DataType = 'boolean';
crt_PT_8e0122_Validity_Yaw.Min = 0.0;
crt_PT_8e0122_Validity_Yaw.Max = 1.0;
crt_PT_8e0122_Validity_Yaw.DocUnits = '';
crt_PT_8e0122_Validity_Yaw.Dimensions = 1;
crt_PT_8e0122_Validity_Yaw.Complexity = 'real';
crt_PT_8e0122_Validity_Yaw.SampleTime = -1;
crt_PT_8e0122_Validity_Yaw.SamplingMode = 'Sample based';
crt_PT_8e0122_Validity_Yaw.InitialValue = '';
% Signal crt_PT_8e0122_Validity_Pitch
crt_PT_8e0122_Validity_Pitch = Simulink.Signal;
crt_PT_8e0122_Validity_Pitch.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0122_Validity_Pitch.RTWInfo.Alias = '';
crt_PT_8e0122_Validity_Pitch.Description = ...
  ['Frame: RT_SB_INS_Attitude, 9306402 (0x8e0122).' char(10) ...
   'Signal: Validity_Pitch.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0122_Validity_Pitch.DataType = 'boolean';
crt_PT_8e0122_Validity_Pitch.Min = 0.0;
crt_PT_8e0122_Validity_Pitch.Max = 1.0;
crt_PT_8e0122_Validity_Pitch.DocUnits = '';
crt_PT_8e0122_Validity_Pitch.Dimensions = 1;
crt_PT_8e0122_Validity_Pitch.Complexity = 'real';
crt_PT_8e0122_Validity_Pitch.SampleTime = -1;
crt_PT_8e0122_Validity_Pitch.SamplingMode = 'Sample based';
crt_PT_8e0122_Validity_Pitch.InitialValue = '';
% Signal crt_PT_8e0122_Validity_Roll
crt_PT_8e0122_Validity_Roll = Simulink.Signal;
crt_PT_8e0122_Validity_Roll.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0122_Validity_Roll.RTWInfo.Alias = '';
crt_PT_8e0122_Validity_Roll.Description = ...
  ['Frame: RT_SB_INS_Attitude, 9306402 (0x8e0122).' char(10) ...
   'Signal: Validity_Roll.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0122_Validity_Roll.DataType = 'boolean';
crt_PT_8e0122_Validity_Roll.Min = 0.0;
crt_PT_8e0122_Validity_Roll.Max = 1.0;
crt_PT_8e0122_Validity_Roll.DocUnits = '';
crt_PT_8e0122_Validity_Roll.Dimensions = 1;
crt_PT_8e0122_Validity_Roll.Complexity = 'real';
crt_PT_8e0122_Validity_Roll.SampleTime = -1;
crt_PT_8e0122_Validity_Roll.SamplingMode = 'Sample based';
crt_PT_8e0122_Validity_Roll.InitialValue = '';
% Signal crt_PT_8e0122_Accuracy_Attitude
crt_PT_8e0122_Accuracy_Attitude = Simulink.Signal;
crt_PT_8e0122_Accuracy_Attitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0122_Accuracy_Attitude.RTWInfo.Alias = '';
crt_PT_8e0122_Accuracy_Attitude.Description = ...
  ['Frame: RT_SB_INS_Attitude, 9306402 (0x8e0122).' char(10) ...
   'Signal: Accuracy_Attitude.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8e0122_Accuracy_Attitude.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8e0122_Accuracy_Attitude.Min = 0.0;
crt_PT_8e0122_Accuracy_Attitude.Max = 255.0;
crt_PT_8e0122_Accuracy_Attitude.DocUnits = '';
crt_PT_8e0122_Accuracy_Attitude.Dimensions = 1;
crt_PT_8e0122_Accuracy_Attitude.Complexity = 'real';
crt_PT_8e0122_Accuracy_Attitude.SampleTime = -1;
crt_PT_8e0122_Accuracy_Attitude.SamplingMode = 'Sample based';
crt_PT_8e0122_Accuracy_Attitude.InitialValue = '';
% Signal crt_PT_8e0122_Attitude_Yaw
crt_PT_8e0122_Attitude_Yaw = Simulink.Signal;
crt_PT_8e0122_Attitude_Yaw.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0122_Attitude_Yaw.RTWInfo.Alias = '';
crt_PT_8e0122_Attitude_Yaw.Description = ...
  ['Frame: RT_SB_INS_Attitude, 9306402 (0x8e0122).' char(10) ...
   'Signal: Attitude_Yaw.' char(10) ...
   'Range (world values): -360.0 ... 360.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8e0122_Attitude_Yaw.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8e0122_Attitude_Yaw.Min = -360.0;
crt_PT_8e0122_Attitude_Yaw.Max = 360.0;
crt_PT_8e0122_Attitude_Yaw.DocUnits = 'degrees';
crt_PT_8e0122_Attitude_Yaw.Dimensions = 1;
crt_PT_8e0122_Attitude_Yaw.Complexity = 'real';
crt_PT_8e0122_Attitude_Yaw.SampleTime = -1;
crt_PT_8e0122_Attitude_Yaw.SamplingMode = 'Sample based';
crt_PT_8e0122_Attitude_Yaw.InitialValue = '';
% Signal crt_PT_8e0122_Attitude_Pitch
crt_PT_8e0122_Attitude_Pitch = Simulink.Signal;
crt_PT_8e0122_Attitude_Pitch.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0122_Attitude_Pitch.RTWInfo.Alias = '';
crt_PT_8e0122_Attitude_Pitch.Description = ...
  ['Frame: RT_SB_INS_Attitude, 9306402 (0x8e0122).' char(10) ...
   'Signal: Attitude_Pitch.' char(10) ...
   'Range (world values): -360.0 ... 360.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8e0122_Attitude_Pitch.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8e0122_Attitude_Pitch.Min = -360.0;
crt_PT_8e0122_Attitude_Pitch.Max = 360.0;
crt_PT_8e0122_Attitude_Pitch.DocUnits = 'degrees';
crt_PT_8e0122_Attitude_Pitch.Dimensions = 1;
crt_PT_8e0122_Attitude_Pitch.Complexity = 'real';
crt_PT_8e0122_Attitude_Pitch.SampleTime = -1;
crt_PT_8e0122_Attitude_Pitch.SamplingMode = 'Sample based';
crt_PT_8e0122_Attitude_Pitch.InitialValue = '';
% Signal crt_PT_8e0122_Attitude_Roll
crt_PT_8e0122_Attitude_Roll = Simulink.Signal;
crt_PT_8e0122_Attitude_Roll.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8e0122_Attitude_Roll.RTWInfo.Alias = '';
crt_PT_8e0122_Attitude_Roll.Description = ...
  ['Frame: RT_SB_INS_Attitude, 9306402 (0x8e0122).' char(10) ...
   'Signal: Attitude_Roll.' char(10) ...
   'Range (world values): -360.0 ... 360.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8e0122_Attitude_Roll.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8e0122_Attitude_Roll.Min = -360.0;
crt_PT_8e0122_Attitude_Roll.Max = 360.0;
crt_PT_8e0122_Attitude_Roll.DocUnits = 'degrees';
crt_PT_8e0122_Attitude_Roll.Dimensions = 1;
crt_PT_8e0122_Attitude_Roll.Complexity = 'real';
crt_PT_8e0122_Attitude_Roll.SampleTime = -1;
crt_PT_8e0122_Attitude_Roll.SamplingMode = 'Sample based';
crt_PT_8e0122_Attitude_Roll.InitialValue = '';

% Frame RT_SB_Output_Status, 9240866 (0x8d0122)
% Signal crt_PT_8d0122_Validity_Status_Timestamp
crt_PT_8d0122_Validity_Status_Timestamp = Simulink.Signal;
crt_PT_8d0122_Validity_Status_Timestamp.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0122_Validity_Status_Timestamp.RTWInfo.Alias = '';
crt_PT_8d0122_Validity_Status_Timestamp.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Output_Status, 9240866 (0x8d0122).' char(10) ...
   'Signal: Validity_Status_Timestamp.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8d0122_Validity_Status_Timestamp.DataType = 'boolean';
crt_PT_8d0122_Validity_Status_Timestamp.Min = 0.0;
crt_PT_8d0122_Validity_Status_Timestamp.Max = 1.0;
crt_PT_8d0122_Validity_Status_Timestamp.DocUnits = '';
crt_PT_8d0122_Validity_Status_Timestamp.Dimensions = 1;
crt_PT_8d0122_Validity_Status_Timestamp.Complexity = 'real';
crt_PT_8d0122_Validity_Status_Timestamp.SampleTime = -1;
crt_PT_8d0122_Validity_Status_Timestamp.SamplingMode = 'Sample based';
crt_PT_8d0122_Validity_Status_Timestamp.InitialValue = '';
% Signal crt_PT_8d0122_Status_Analogue_1
crt_PT_8d0122_Status_Analogue_1 = Simulink.Signal;
crt_PT_8d0122_Status_Analogue_1.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0122_Status_Analogue_1.RTWInfo.Alias = '';
crt_PT_8d0122_Status_Analogue_1.Description = ...
  ['Analogue output status for channel 1.' char(10) ...
   'Frame: RT_SB_Output_Status, 9240866 (0x8d0122).' char(10) ...
   'Signal: Status_Analogue_1.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8d0122_Status_Analogue_1.DataType = 'boolean';
crt_PT_8d0122_Status_Analogue_1.Min = 0.0;
crt_PT_8d0122_Status_Analogue_1.Max = 1.0;
crt_PT_8d0122_Status_Analogue_1.DocUnits = '';
crt_PT_8d0122_Status_Analogue_1.Dimensions = 1;
crt_PT_8d0122_Status_Analogue_1.Complexity = 'real';
crt_PT_8d0122_Status_Analogue_1.SampleTime = -1;
crt_PT_8d0122_Status_Analogue_1.SamplingMode = 'Sample based';
crt_PT_8d0122_Status_Analogue_1.InitialValue = '';
% Signal crt_PT_8d0122_Status_Analogue_2
crt_PT_8d0122_Status_Analogue_2 = Simulink.Signal;
crt_PT_8d0122_Status_Analogue_2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0122_Status_Analogue_2.RTWInfo.Alias = '';
crt_PT_8d0122_Status_Analogue_2.Description = ...
  ['Analogue output status for channel 1.' char(10) ...
   'Frame: RT_SB_Output_Status, 9240866 (0x8d0122).' char(10) ...
   'Signal: Status_Analogue_2.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8d0122_Status_Analogue_2.DataType = 'boolean';
crt_PT_8d0122_Status_Analogue_2.Min = 0.0;
crt_PT_8d0122_Status_Analogue_2.Max = 1.0;
crt_PT_8d0122_Status_Analogue_2.DocUnits = '';
crt_PT_8d0122_Status_Analogue_2.Dimensions = 1;
crt_PT_8d0122_Status_Analogue_2.Complexity = 'real';
crt_PT_8d0122_Status_Analogue_2.SampleTime = -1;
crt_PT_8d0122_Status_Analogue_2.SamplingMode = 'Sample based';
crt_PT_8d0122_Status_Analogue_2.InitialValue = '';
% Signal crt_PT_8d0122_Status_Analogue_3
crt_PT_8d0122_Status_Analogue_3 = Simulink.Signal;
crt_PT_8d0122_Status_Analogue_3.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0122_Status_Analogue_3.RTWInfo.Alias = '';
crt_PT_8d0122_Status_Analogue_3.Description = ...
  ['Analogue output status for channel 3.' char(10) ...
   'Frame: RT_SB_Output_Status, 9240866 (0x8d0122).' char(10) ...
   'Signal: Status_Analogue_3.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8d0122_Status_Analogue_3.DataType = 'boolean';
crt_PT_8d0122_Status_Analogue_3.Min = 0.0;
crt_PT_8d0122_Status_Analogue_3.Max = 1.0;
crt_PT_8d0122_Status_Analogue_3.DocUnits = '';
crt_PT_8d0122_Status_Analogue_3.Dimensions = 1;
crt_PT_8d0122_Status_Analogue_3.Complexity = 'real';
crt_PT_8d0122_Status_Analogue_3.SampleTime = -1;
crt_PT_8d0122_Status_Analogue_3.SamplingMode = 'Sample based';
crt_PT_8d0122_Status_Analogue_3.InitialValue = '';
% Signal crt_PT_8d0122_Status_Analogue_4
crt_PT_8d0122_Status_Analogue_4 = Simulink.Signal;
crt_PT_8d0122_Status_Analogue_4.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0122_Status_Analogue_4.RTWInfo.Alias = '';
crt_PT_8d0122_Status_Analogue_4.Description = ...
  ['Analogue output status for channel 4.' char(10) ...
   'Frame: RT_SB_Output_Status, 9240866 (0x8d0122).' char(10) ...
   'Signal: Status_Analogue_4.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8d0122_Status_Analogue_4.DataType = 'boolean';
crt_PT_8d0122_Status_Analogue_4.Min = 0.0;
crt_PT_8d0122_Status_Analogue_4.Max = 1.0;
crt_PT_8d0122_Status_Analogue_4.DocUnits = '';
crt_PT_8d0122_Status_Analogue_4.Dimensions = 1;
crt_PT_8d0122_Status_Analogue_4.Complexity = 'real';
crt_PT_8d0122_Status_Analogue_4.SampleTime = -1;
crt_PT_8d0122_Status_Analogue_4.SamplingMode = 'Sample based';
crt_PT_8d0122_Status_Analogue_4.InitialValue = '';
% Signal crt_PT_8d0122_Status_Pulse_Output
crt_PT_8d0122_Status_Pulse_Output = Simulink.Signal;
crt_PT_8d0122_Status_Pulse_Output.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0122_Status_Pulse_Output.RTWInfo.Alias = '';
crt_PT_8d0122_Status_Pulse_Output.Description = ...
  ['Pulse output activity status' char(10) ...
   'Frame: RT_SB_Output_Status, 9240866 (0x8d0122).' char(10) ...
   'Signal: Status_Pulse_Output.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8d0122_Status_Pulse_Output.DataType = 'boolean';
crt_PT_8d0122_Status_Pulse_Output.Min = 0.0;
crt_PT_8d0122_Status_Pulse_Output.Max = 1.0;
crt_PT_8d0122_Status_Pulse_Output.DocUnits = '';
crt_PT_8d0122_Status_Pulse_Output.Dimensions = 1;
crt_PT_8d0122_Status_Pulse_Output.Complexity = 'real';
crt_PT_8d0122_Status_Pulse_Output.SampleTime = -1;
crt_PT_8d0122_Status_Pulse_Output.SamplingMode = 'Sample based';
crt_PT_8d0122_Status_Pulse_Output.InitialValue = '';
% Signal crt_PT_8d0122_Status_Serial_Output_1
crt_PT_8d0122_Status_Serial_Output_1 = Simulink.Signal;
crt_PT_8d0122_Status_Serial_Output_1.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0122_Status_Serial_Output_1.RTWInfo.Alias = '';
crt_PT_8d0122_Status_Serial_Output_1.Description = ...
  ['Status output of serial port 1' char(10) ...
   'Frame: RT_SB_Output_Status, 9240866 (0x8d0122).' char(10) ...
   'Signal: Status_Serial_Output_1.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8d0122_Status_Serial_Output_1.DataType = 'boolean';
crt_PT_8d0122_Status_Serial_Output_1.Min = 0.0;
crt_PT_8d0122_Status_Serial_Output_1.Max = 1.0;
crt_PT_8d0122_Status_Serial_Output_1.DocUnits = '';
crt_PT_8d0122_Status_Serial_Output_1.Dimensions = 1;
crt_PT_8d0122_Status_Serial_Output_1.Complexity = 'real';
crt_PT_8d0122_Status_Serial_Output_1.SampleTime = -1;
crt_PT_8d0122_Status_Serial_Output_1.SamplingMode = 'Sample based';
crt_PT_8d0122_Status_Serial_Output_1.InitialValue = '';
% Signal crt_PT_8d0122_Status_Serial_Output_2
crt_PT_8d0122_Status_Serial_Output_2 = Simulink.Signal;
crt_PT_8d0122_Status_Serial_Output_2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0122_Status_Serial_Output_2.RTWInfo.Alias = '';
crt_PT_8d0122_Status_Serial_Output_2.Description = ...
  ['Status output of serial port 1' char(10) ...
   'Frame: RT_SB_Output_Status, 9240866 (0x8d0122).' char(10) ...
   'Signal: Status_Serial_Output_2.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8d0122_Status_Serial_Output_2.DataType = 'boolean';
crt_PT_8d0122_Status_Serial_Output_2.Min = 0.0;
crt_PT_8d0122_Status_Serial_Output_2.Max = 1.0;
crt_PT_8d0122_Status_Serial_Output_2.DocUnits = '';
crt_PT_8d0122_Status_Serial_Output_2.Dimensions = 1;
crt_PT_8d0122_Status_Serial_Output_2.Complexity = 'real';
crt_PT_8d0122_Status_Serial_Output_2.SampleTime = -1;
crt_PT_8d0122_Status_Serial_Output_2.SamplingMode = 'Sample based';
crt_PT_8d0122_Status_Serial_Output_2.InitialValue = '';
% Signal crt_PT_8d0122_Status_Trigger
crt_PT_8d0122_Status_Trigger = Simulink.Signal;
crt_PT_8d0122_Status_Trigger.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0122_Status_Trigger.RTWInfo.Alias = '';
crt_PT_8d0122_Status_Trigger.Description = ...
  ['Status of the trigger input' char(10) ...
   'Frame: RT_SB_Output_Status, 9240866 (0x8d0122).' char(10) ...
   'Signal: Status_Trigger.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8d0122_Status_Trigger.DataType = 'boolean';
crt_PT_8d0122_Status_Trigger.Min = 0.0;
crt_PT_8d0122_Status_Trigger.Max = 1.0;
crt_PT_8d0122_Status_Trigger.DocUnits = '';
crt_PT_8d0122_Status_Trigger.Dimensions = 1;
crt_PT_8d0122_Status_Trigger.Complexity = 'real';
crt_PT_8d0122_Status_Trigger.SampleTime = -1;
crt_PT_8d0122_Status_Trigger.SamplingMode = 'Sample based';
crt_PT_8d0122_Status_Trigger.InitialValue = '';
% Signal crt_PT_8d0122_GPS_Time
crt_PT_8d0122_GPS_Time = Simulink.Signal;
crt_PT_8d0122_GPS_Time.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0122_GPS_Time.RTWInfo.Alias = '';
crt_PT_8d0122_GPS_Time.Description = ...
  ['GPS time is the time in seconds since midnight GMT on Saturday night.' char(10) ...
   'Frame: RT_SB_Output_Status, 9240866 (0x8d0122).' char(10) ...
   'Signal: GPS_Time.' char(10) ...
   'Range (world values): 0.0 ... 604800.0 [s].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [s]' ...
  ];
crt_PT_8d0122_GPS_Time.DataType = 'fixdt(0, 32, 0.001, 0.0)';
crt_PT_8d0122_GPS_Time.Min = 0.0;
crt_PT_8d0122_GPS_Time.Max = 604800.0;
crt_PT_8d0122_GPS_Time.DocUnits = 's';
crt_PT_8d0122_GPS_Time.Dimensions = 1;
crt_PT_8d0122_GPS_Time.Complexity = 'real';
crt_PT_8d0122_GPS_Time.SampleTime = -1;
crt_PT_8d0122_GPS_Time.SamplingMode = 'Sample based';
crt_PT_8d0122_GPS_Time.InitialValue = '';

% Frame RT_SB_GPS_Heading_Gradient_2, 9180706 (0x8c1622)
% Signal crt_PT_8c1622_Validity_GPS_Heading
crt_PT_8c1622_Validity_GPS_Heading = Simulink.Signal;
crt_PT_8c1622_Validity_GPS_Heading.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1622_Validity_GPS_Heading.RTWInfo.Alias = '';
crt_PT_8c1622_Validity_GPS_Heading.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Heading_Gradient_2, 9180706 (0x8c1622).' char(10) ...
   'Signal: Validity_GPS_Heading.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c1622_Validity_GPS_Heading.DataType = 'boolean';
crt_PT_8c1622_Validity_GPS_Heading.Min = 0.0;
crt_PT_8c1622_Validity_GPS_Heading.Max = 1.0;
crt_PT_8c1622_Validity_GPS_Heading.DocUnits = '';
crt_PT_8c1622_Validity_GPS_Heading.Dimensions = 1;
crt_PT_8c1622_Validity_GPS_Heading.Complexity = 'real';
crt_PT_8c1622_Validity_GPS_Heading.SampleTime = -1;
crt_PT_8c1622_Validity_GPS_Heading.SamplingMode = 'Sample based';
crt_PT_8c1622_Validity_GPS_Heading.InitialValue = '';
% Signal crt_PT_8c1622_Validity_GPS_Gradient
crt_PT_8c1622_Validity_GPS_Gradient = Simulink.Signal;
crt_PT_8c1622_Validity_GPS_Gradient.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1622_Validity_GPS_Gradient.RTWInfo.Alias = '';
crt_PT_8c1622_Validity_GPS_Gradient.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Heading_Gradient_2, 9180706 (0x8c1622).' char(10) ...
   'Signal: Validity_GPS_Gradient.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c1622_Validity_GPS_Gradient.DataType = 'boolean';
crt_PT_8c1622_Validity_GPS_Gradient.Min = 0.0;
crt_PT_8c1622_Validity_GPS_Gradient.Max = 1.0;
crt_PT_8c1622_Validity_GPS_Gradient.DocUnits = '';
crt_PT_8c1622_Validity_GPS_Gradient.Dimensions = 1;
crt_PT_8c1622_Validity_GPS_Gradient.Complexity = 'real';
crt_PT_8c1622_Validity_GPS_Gradient.SampleTime = -1;
crt_PT_8c1622_Validity_GPS_Gradient.SamplingMode = 'Sample based';
crt_PT_8c1622_Validity_GPS_Gradient.InitialValue = '';
% Signal crt_PT_8c1622_Accuracy_GPS_Heading
crt_PT_8c1622_Accuracy_GPS_Heading = Simulink.Signal;
crt_PT_8c1622_Accuracy_GPS_Heading.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1622_Accuracy_GPS_Heading.RTWInfo.Alias = '';
crt_PT_8c1622_Accuracy_GPS_Heading.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_GPS_Heading_Gradient_2, 9180706 (0x8c1622).' char(10) ...
   'Signal: Accuracy_GPS_Heading.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c1622_Accuracy_GPS_Heading.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c1622_Accuracy_GPS_Heading.Min = 0.0;
crt_PT_8c1622_Accuracy_GPS_Heading.Max = 255.0;
crt_PT_8c1622_Accuracy_GPS_Heading.DocUnits = '';
crt_PT_8c1622_Accuracy_GPS_Heading.Dimensions = 1;
crt_PT_8c1622_Accuracy_GPS_Heading.Complexity = 'real';
crt_PT_8c1622_Accuracy_GPS_Heading.SampleTime = -1;
crt_PT_8c1622_Accuracy_GPS_Heading.SamplingMode = 'Sample based';
crt_PT_8c1622_Accuracy_GPS_Heading.InitialValue = '';
% Signal crt_PT_8c1622_GPS_Heading_2
crt_PT_8c1622_GPS_Heading_2 = Simulink.Signal;
crt_PT_8c1622_GPS_Heading_2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1622_GPS_Heading_2.RTWInfo.Alias = '';
crt_PT_8c1622_GPS_Heading_2.Description = ...
  ['This is GPS heading in the range 0 - 360., the direction that the vehicle is travelling in the local horizontal plane.' char(10) ...
   'Frame: RT_SB_GPS_Heading_Gradient_2, 9180706 (0x8c1622).' char(10) ...
   'Signal: GPS_Heading_2.' char(10) ...
   'Range (world values): 0.0 ... 360.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8c1622_GPS_Heading_2.DataType = 'fixdt(0, 16, 0.01, 0.0)';
crt_PT_8c1622_GPS_Heading_2.Min = 0.0;
crt_PT_8c1622_GPS_Heading_2.Max = 360.0;
crt_PT_8c1622_GPS_Heading_2.DocUnits = 'degrees';
crt_PT_8c1622_GPS_Heading_2.Dimensions = 1;
crt_PT_8c1622_GPS_Heading_2.Complexity = 'real';
crt_PT_8c1622_GPS_Heading_2.SampleTime = -1;
crt_PT_8c1622_GPS_Heading_2.SamplingMode = 'Sample based';
crt_PT_8c1622_GPS_Heading_2.InitialValue = '';
% Signal crt_PT_8c1622_Accuracy_GPS_Gradient
crt_PT_8c1622_Accuracy_GPS_Gradient = Simulink.Signal;
crt_PT_8c1622_Accuracy_GPS_Gradient.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1622_Accuracy_GPS_Gradient.RTWInfo.Alias = '';
crt_PT_8c1622_Accuracy_GPS_Gradient.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_GPS_Heading_Gradient_2, 9180706 (0x8c1622).' char(10) ...
   'Signal: Accuracy_GPS_Gradient.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c1622_Accuracy_GPS_Gradient.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c1622_Accuracy_GPS_Gradient.Min = 0.0;
crt_PT_8c1622_Accuracy_GPS_Gradient.Max = 255.0;
crt_PT_8c1622_Accuracy_GPS_Gradient.DocUnits = '';
crt_PT_8c1622_Accuracy_GPS_Gradient.Dimensions = 1;
crt_PT_8c1622_Accuracy_GPS_Gradient.Complexity = 'real';
crt_PT_8c1622_Accuracy_GPS_Gradient.SampleTime = -1;
crt_PT_8c1622_Accuracy_GPS_Gradient.SamplingMode = 'Sample based';
crt_PT_8c1622_Accuracy_GPS_Gradient.InitialValue = '';
% Signal crt_PT_8c1622_GPS_Gradient
crt_PT_8c1622_GPS_Gradient = Simulink.Signal;
crt_PT_8c1622_GPS_Gradient.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1622_GPS_Gradient.RTWInfo.Alias = '';
crt_PT_8c1622_GPS_Gradient.Description = ...
  ['This is GPS gradient, i.e. the vertical direction that the vehicle is travelling, NOT pointing (pitch).' char(10) ...
   'Frame: RT_SB_GPS_Heading_Gradient_2, 9180706 (0x8c1622).' char(10) ...
   'Signal: GPS_Gradient.' char(10) ...
   'Range (world values): -90.0 ... 90.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8c1622_GPS_Gradient.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8c1622_GPS_Gradient.Min = -90.0;
crt_PT_8c1622_GPS_Gradient.Max = 90.0;
crt_PT_8c1622_GPS_Gradient.DocUnits = 'degrees';
crt_PT_8c1622_GPS_Gradient.Dimensions = 1;
crt_PT_8c1622_GPS_Gradient.Complexity = 'real';
crt_PT_8c1622_GPS_Gradient.SampleTime = -1;
crt_PT_8c1622_GPS_Gradient.SamplingMode = 'Sample based';
crt_PT_8c1622_GPS_Gradient.InitialValue = '';

% Frame RT_SB_Cumulative_Distance_2, 8397090 (0x802122)
% Signal crt_PT_802122_Validity_Cumulative_Time
crt_PT_802122_Validity_Cumulative_Time = Simulink.Signal;
crt_PT_802122_Validity_Cumulative_Time.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_802122_Validity_Cumulative_Time.RTWInfo.Alias = '';
crt_PT_802122_Validity_Cumulative_Time.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Cumulative_Distance_2, 8397090 (0x802122).' char(10) ...
   'Signal: Validity_Cumulative_Time.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_802122_Validity_Cumulative_Time.DataType = 'boolean';
crt_PT_802122_Validity_Cumulative_Time.Min = 0.0;
crt_PT_802122_Validity_Cumulative_Time.Max = 1.0;
crt_PT_802122_Validity_Cumulative_Time.DocUnits = '';
crt_PT_802122_Validity_Cumulative_Time.Dimensions = 1;
crt_PT_802122_Validity_Cumulative_Time.Complexity = 'real';
crt_PT_802122_Validity_Cumulative_Time.SampleTime = -1;
crt_PT_802122_Validity_Cumulative_Time.SamplingMode = 'Sample based';
crt_PT_802122_Validity_Cumulative_Time.InitialValue = '';
% Signal crt_PT_802122_Validity_Cumulative_Distance
crt_PT_802122_Validity_Cumulative_Distance = Simulink.Signal;
crt_PT_802122_Validity_Cumulative_Distance.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_802122_Validity_Cumulative_Distance.RTWInfo.Alias = '';
crt_PT_802122_Validity_Cumulative_Distance.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Cumulative_Distance_2, 8397090 (0x802122).' char(10) ...
   'Signal: Validity_Cumulative_Distance.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_802122_Validity_Cumulative_Distance.DataType = 'boolean';
crt_PT_802122_Validity_Cumulative_Distance.Min = 0.0;
crt_PT_802122_Validity_Cumulative_Distance.Max = 1.0;
crt_PT_802122_Validity_Cumulative_Distance.DocUnits = '';
crt_PT_802122_Validity_Cumulative_Distance.Dimensions = 1;
crt_PT_802122_Validity_Cumulative_Distance.Complexity = 'real';
crt_PT_802122_Validity_Cumulative_Distance.SampleTime = -1;
crt_PT_802122_Validity_Cumulative_Distance.SamplingMode = 'Sample based';
crt_PT_802122_Validity_Cumulative_Distance.InitialValue = '';
% Signal crt_PT_802122_Cumulative_Time
crt_PT_802122_Cumulative_Time = Simulink.Signal;
crt_PT_802122_Cumulative_Time.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_802122_Cumulative_Time.RTWInfo.Alias = '';
crt_PT_802122_Cumulative_Time.Description = ...
  ['Frame: RT_SB_Cumulative_Distance_2, 8397090 (0x802122).' char(10) ...
   'Signal: Cumulative_Time.' char(10) ...
   'Range (world values): 0.0 ... 167772.0 [s].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [s]' ...
  ];
crt_PT_802122_Cumulative_Time.DataType = 'fixdt(0, 32, 0.01, 0.0)';
crt_PT_802122_Cumulative_Time.Min = 0.0;
crt_PT_802122_Cumulative_Time.Max = 167772.0;
crt_PT_802122_Cumulative_Time.DocUnits = 's';
crt_PT_802122_Cumulative_Time.Dimensions = 1;
crt_PT_802122_Cumulative_Time.Complexity = 'real';
crt_PT_802122_Cumulative_Time.SampleTime = -1;
crt_PT_802122_Cumulative_Time.SamplingMode = 'Sample based';
crt_PT_802122_Cumulative_Time.InitialValue = '';
% Signal crt_PT_802122_Cumulative_Distance
crt_PT_802122_Cumulative_Distance = Simulink.Signal;
crt_PT_802122_Cumulative_Distance.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_802122_Cumulative_Distance.RTWInfo.Alias = '';
crt_PT_802122_Cumulative_Distance.Description = ...
  ['Frame: RT_SB_Cumulative_Distance_2, 8397090 (0x802122).' char(10) ...
   'Signal: Cumulative_Distance.' char(10) ...
   'Range (world values): 0.0 ... 4294970.0 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_802122_Cumulative_Distance.DataType = 'fixdt(0, 32, 0.001, 0.0)';
crt_PT_802122_Cumulative_Distance.Min = 0.0;
crt_PT_802122_Cumulative_Distance.Max = 4294970.0;
crt_PT_802122_Cumulative_Distance.DocUnits = 'm';
crt_PT_802122_Cumulative_Distance.Dimensions = 1;
crt_PT_802122_Cumulative_Distance.Complexity = 'real';
crt_PT_802122_Cumulative_Distance.SampleTime = -1;
crt_PT_802122_Cumulative_Distance.SamplingMode = 'Sample based';
crt_PT_802122_Cumulative_Distance.InitialValue = '';

% Frame RT_SB_Cumulative_Distance_1, 8396834 (0x802022)
% Signal crt_PT_802022_Validity_Cumulative_Time
crt_PT_802022_Validity_Cumulative_Time = Simulink.Signal;
crt_PT_802022_Validity_Cumulative_Time.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_802022_Validity_Cumulative_Time.RTWInfo.Alias = '';
crt_PT_802022_Validity_Cumulative_Time.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Cumulative_Distance_1, 8396834 (0x802022).' char(10) ...
   'Signal: Validity_Cumulative_Time.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_802022_Validity_Cumulative_Time.DataType = 'boolean';
crt_PT_802022_Validity_Cumulative_Time.Min = 0.0;
crt_PT_802022_Validity_Cumulative_Time.Max = 1.0;
crt_PT_802022_Validity_Cumulative_Time.DocUnits = '';
crt_PT_802022_Validity_Cumulative_Time.Dimensions = 1;
crt_PT_802022_Validity_Cumulative_Time.Complexity = 'real';
crt_PT_802022_Validity_Cumulative_Time.SampleTime = -1;
crt_PT_802022_Validity_Cumulative_Time.SamplingMode = 'Sample based';
crt_PT_802022_Validity_Cumulative_Time.InitialValue = '';
% Signal crt_PT_802022_Validity_Cumulative_Distance
crt_PT_802022_Validity_Cumulative_Distance = Simulink.Signal;
crt_PT_802022_Validity_Cumulative_Distance.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_802022_Validity_Cumulative_Distance.RTWInfo.Alias = '';
crt_PT_802022_Validity_Cumulative_Distance.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Cumulative_Distance_1, 8396834 (0x802022).' char(10) ...
   'Signal: Validity_Cumulative_Distance.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_802022_Validity_Cumulative_Distance.DataType = 'boolean';
crt_PT_802022_Validity_Cumulative_Distance.Min = 0.0;
crt_PT_802022_Validity_Cumulative_Distance.Max = 1.0;
crt_PT_802022_Validity_Cumulative_Distance.DocUnits = '';
crt_PT_802022_Validity_Cumulative_Distance.Dimensions = 1;
crt_PT_802022_Validity_Cumulative_Distance.Complexity = 'real';
crt_PT_802022_Validity_Cumulative_Distance.SampleTime = -1;
crt_PT_802022_Validity_Cumulative_Distance.SamplingMode = 'Sample based';
crt_PT_802022_Validity_Cumulative_Distance.InitialValue = '';
% Signal crt_PT_802022_Cumulative_Time
crt_PT_802022_Cumulative_Time = Simulink.Signal;
crt_PT_802022_Cumulative_Time.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_802022_Cumulative_Time.RTWInfo.Alias = '';
crt_PT_802022_Cumulative_Time.Description = ...
  ['Frame: RT_SB_Cumulative_Distance_1, 8396834 (0x802022).' char(10) ...
   'Signal: Cumulative_Time.' char(10) ...
   'Range (world values): 0.0 ... 167772.0 [s].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [s]' ...
  ];
crt_PT_802022_Cumulative_Time.DataType = 'fixdt(0, 32, 0.01, 0.0)';
crt_PT_802022_Cumulative_Time.Min = 0.0;
crt_PT_802022_Cumulative_Time.Max = 167772.0;
crt_PT_802022_Cumulative_Time.DocUnits = 's';
crt_PT_802022_Cumulative_Time.Dimensions = 1;
crt_PT_802022_Cumulative_Time.Complexity = 'real';
crt_PT_802022_Cumulative_Time.SampleTime = -1;
crt_PT_802022_Cumulative_Time.SamplingMode = 'Sample based';
crt_PT_802022_Cumulative_Time.InitialValue = '';
% Signal crt_PT_802022_Cumulative_Distance
crt_PT_802022_Cumulative_Distance = Simulink.Signal;
crt_PT_802022_Cumulative_Distance.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_802022_Cumulative_Distance.RTWInfo.Alias = '';
crt_PT_802022_Cumulative_Distance.Description = ...
  ['Frame: RT_SB_Cumulative_Distance_1, 8396834 (0x802022).' char(10) ...
   'Signal: Cumulative_Distance.' char(10) ...
   'Range (world values): 0.0 ... 4294970.0 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_802022_Cumulative_Distance.DataType = 'fixdt(0, 32, 0.001, 0.0)';
crt_PT_802022_Cumulative_Distance.Min = 0.0;
crt_PT_802022_Cumulative_Distance.Max = 4294970.0;
crt_PT_802022_Cumulative_Distance.DocUnits = 'm';
crt_PT_802022_Cumulative_Distance.Dimensions = 1;
crt_PT_802022_Cumulative_Distance.Complexity = 'real';
crt_PT_802022_Cumulative_Distance.SampleTime = -1;
crt_PT_802022_Cumulative_Distance.SamplingMode = 'Sample based';
crt_PT_802022_Cumulative_Distance.InitialValue = '';

% Frame RT_SB_Trigger_Timestamp, 9240610 (0x8d0022)
% Signal crt_PT_8d0022_Validity_Trigger_Timestamp
crt_PT_8d0022_Validity_Trigger_Timestamp = Simulink.Signal;
crt_PT_8d0022_Validity_Trigger_Timestamp.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0022_Validity_Trigger_Timestamp.RTWInfo.Alias = '';
crt_PT_8d0022_Validity_Trigger_Timestamp.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Trigger_Timestamp, 9240610 (0x8d0022).' char(10) ...
   'Signal: Validity_Trigger_Timestamp.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8d0022_Validity_Trigger_Timestamp.DataType = 'boolean';
crt_PT_8d0022_Validity_Trigger_Timestamp.Min = 0.0;
crt_PT_8d0022_Validity_Trigger_Timestamp.Max = 1.0;
crt_PT_8d0022_Validity_Trigger_Timestamp.DocUnits = '';
crt_PT_8d0022_Validity_Trigger_Timestamp.Dimensions = 1;
crt_PT_8d0022_Validity_Trigger_Timestamp.Complexity = 'real';
crt_PT_8d0022_Validity_Trigger_Timestamp.SampleTime = -1;
crt_PT_8d0022_Validity_Trigger_Timestamp.SamplingMode = 'Sample based';
crt_PT_8d0022_Validity_Trigger_Timestamp.InitialValue = '';
% Signal crt_PT_8d0022_Accuracy_Trigger_Timestamp
crt_PT_8d0022_Accuracy_Trigger_Timestamp = Simulink.Signal;
crt_PT_8d0022_Accuracy_Trigger_Timestamp.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0022_Accuracy_Trigger_Timestamp.RTWInfo.Alias = '';
crt_PT_8d0022_Accuracy_Trigger_Timestamp.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_Trigger_Timestamp, 9240610 (0x8d0022).' char(10) ...
   'Signal: Accuracy_Trigger_Timestamp.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8d0022_Accuracy_Trigger_Timestamp.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8d0022_Accuracy_Trigger_Timestamp.Min = 0.0;
crt_PT_8d0022_Accuracy_Trigger_Timestamp.Max = 255.0;
crt_PT_8d0022_Accuracy_Trigger_Timestamp.DocUnits = '';
crt_PT_8d0022_Accuracy_Trigger_Timestamp.Dimensions = 1;
crt_PT_8d0022_Accuracy_Trigger_Timestamp.Complexity = 'real';
crt_PT_8d0022_Accuracy_Trigger_Timestamp.SampleTime = -1;
crt_PT_8d0022_Accuracy_Trigger_Timestamp.SamplingMode = 'Sample based';
crt_PT_8d0022_Accuracy_Trigger_Timestamp.InitialValue = '';
% Signal crt_PT_8d0022_Trigger_Number
crt_PT_8d0022_Trigger_Number = Simulink.Signal;
crt_PT_8d0022_Trigger_Number.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0022_Trigger_Number.RTWInfo.Alias = '';
crt_PT_8d0022_Trigger_Number.Description = ...
  ['This is the ID of the trigger that generated the event, as marked on the case of the logger' char(10) ...
   'Frame: RT_SB_Trigger_Timestamp, 9240610 (0x8d0022).' char(10) ...
   'Signal: Trigger_Number.' char(10) ...
   'Range (world values): 0.0 ... 128.0 [].' char(10) ...
   'Scaling: WorldValue = 1.0*BinaryValue + 1.0 []' ...
  ];
crt_PT_8d0022_Trigger_Number.DataType = 'fixdt(0, 8,  1.0, 1.0)';
crt_PT_8d0022_Trigger_Number.Min = 0.0;
crt_PT_8d0022_Trigger_Number.Max = 128.0;
crt_PT_8d0022_Trigger_Number.DocUnits = '';
crt_PT_8d0022_Trigger_Number.Dimensions = 1;
crt_PT_8d0022_Trigger_Number.Complexity = 'real';
crt_PT_8d0022_Trigger_Number.SampleTime = -1;
crt_PT_8d0022_Trigger_Number.SamplingMode = 'Sample based';
crt_PT_8d0022_Trigger_Number.InitialValue = '';
% Signal crt_PT_8d0022_Trigger_Timestamp_Type
crt_PT_8d0022_Trigger_Timestamp_Type = Simulink.Signal;
crt_PT_8d0022_Trigger_Timestamp_Type.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0022_Trigger_Timestamp_Type.RTWInfo.Alias = '';
crt_PT_8d0022_Trigger_Timestamp_Type.Description = ...
  ['Frame: RT_SB_Trigger_Timestamp, 9240610 (0x8d0022).' char(10) ...
   'Signal: Trigger_Timestamp_Type.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8d0022_Trigger_Timestamp_Type.DataType = 'boolean';
crt_PT_8d0022_Trigger_Timestamp_Type.Min = 0.0;
crt_PT_8d0022_Trigger_Timestamp_Type.Max = 1.0;
crt_PT_8d0022_Trigger_Timestamp_Type.DocUnits = '';
crt_PT_8d0022_Trigger_Timestamp_Type.Dimensions = 1;
crt_PT_8d0022_Trigger_Timestamp_Type.Complexity = 'real';
crt_PT_8d0022_Trigger_Timestamp_Type.SampleTime = -1;
crt_PT_8d0022_Trigger_Timestamp_Type.SamplingMode = 'Sample based';
crt_PT_8d0022_Trigger_Timestamp_Type.InitialValue = '';
% Signal crt_PT_8d0022_GPS_High_Resolution_Time
crt_PT_8d0022_GPS_High_Resolution_Time = Simulink.Signal;
crt_PT_8d0022_GPS_High_Resolution_Time.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0022_GPS_High_Resolution_Time.RTWInfo.Alias = '';
crt_PT_8d0022_GPS_High_Resolution_Time.Description = ...
  ['GPS time of week to micro-second resolution.' char(10) ...
   'Frame: RT_SB_Trigger_Timestamp, 9240610 (0x8d0022).' char(10) ...
   'Signal: GPS_High_Resolution_Time.' char(10) ...
   'Range (world values): 0.0 ... 604800.0 [s].' char(10) ...
   'Scaling: WorldValue = 1.0E-6*BinaryValue + 0.0 [s]' ...
  ];
crt_PT_8d0022_GPS_High_Resolution_Time.DataType = 'fixdt(0, 64, 1.0E-6, 0.0)';
crt_PT_8d0022_GPS_High_Resolution_Time.Min = 0.0;
crt_PT_8d0022_GPS_High_Resolution_Time.Max = 604800.0;
crt_PT_8d0022_GPS_High_Resolution_Time.DocUnits = 's';
crt_PT_8d0022_GPS_High_Resolution_Time.Dimensions = 1;
crt_PT_8d0022_GPS_High_Resolution_Time.Complexity = 'real';
crt_PT_8d0022_GPS_High_Resolution_Time.SampleTime = -1;
crt_PT_8d0022_GPS_High_Resolution_Time.SamplingMode = 'Sample based';
crt_PT_8d0022_GPS_High_Resolution_Time.InitialValue = '';

% Frame RT_IMU06_Gyro_Rates, 8388897 (0x800121)
% Signal crt_PT_800121_Validity_Gyro_Rate_Yaw
crt_PT_800121_Validity_Gyro_Rate_Yaw = Simulink.Signal;
crt_PT_800121_Validity_Gyro_Rate_Yaw.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800121_Validity_Gyro_Rate_Yaw.RTWInfo.Alias = '';
crt_PT_800121_Validity_Gyro_Rate_Yaw.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_IMU06_Gyro_Rates, 8388897 (0x800121).' char(10) ...
   'Signal: Validity_Gyro_Rate_Yaw.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800121_Validity_Gyro_Rate_Yaw.DataType = 'boolean';
crt_PT_800121_Validity_Gyro_Rate_Yaw.Min = 0.0;
crt_PT_800121_Validity_Gyro_Rate_Yaw.Max = 1.0;
crt_PT_800121_Validity_Gyro_Rate_Yaw.DocUnits = '';
crt_PT_800121_Validity_Gyro_Rate_Yaw.Dimensions = 1;
crt_PT_800121_Validity_Gyro_Rate_Yaw.Complexity = 'real';
crt_PT_800121_Validity_Gyro_Rate_Yaw.SampleTime = -1;
crt_PT_800121_Validity_Gyro_Rate_Yaw.SamplingMode = 'Sample based';
crt_PT_800121_Validity_Gyro_Rate_Yaw.InitialValue = '';
% Signal crt_PT_800121_Validity_Gyro_Rate_Pitch
crt_PT_800121_Validity_Gyro_Rate_Pitch = Simulink.Signal;
crt_PT_800121_Validity_Gyro_Rate_Pitch.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800121_Validity_Gyro_Rate_Pitch.RTWInfo.Alias = '';
crt_PT_800121_Validity_Gyro_Rate_Pitch.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_IMU06_Gyro_Rates, 8388897 (0x800121).' char(10) ...
   'Signal: Validity_Gyro_Rate_Pitch.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800121_Validity_Gyro_Rate_Pitch.DataType = 'boolean';
crt_PT_800121_Validity_Gyro_Rate_Pitch.Min = 0.0;
crt_PT_800121_Validity_Gyro_Rate_Pitch.Max = 1.0;
crt_PT_800121_Validity_Gyro_Rate_Pitch.DocUnits = '';
crt_PT_800121_Validity_Gyro_Rate_Pitch.Dimensions = 1;
crt_PT_800121_Validity_Gyro_Rate_Pitch.Complexity = 'real';
crt_PT_800121_Validity_Gyro_Rate_Pitch.SampleTime = -1;
crt_PT_800121_Validity_Gyro_Rate_Pitch.SamplingMode = 'Sample based';
crt_PT_800121_Validity_Gyro_Rate_Pitch.InitialValue = '';
% Signal crt_PT_800121_Validity_Gyro_Rate_Roll
crt_PT_800121_Validity_Gyro_Rate_Roll = Simulink.Signal;
crt_PT_800121_Validity_Gyro_Rate_Roll.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800121_Validity_Gyro_Rate_Roll.RTWInfo.Alias = '';
crt_PT_800121_Validity_Gyro_Rate_Roll.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_IMU06_Gyro_Rates, 8388897 (0x800121).' char(10) ...
   'Signal: Validity_Gyro_Rate_Roll.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800121_Validity_Gyro_Rate_Roll.DataType = 'boolean';
crt_PT_800121_Validity_Gyro_Rate_Roll.Min = 0.0;
crt_PT_800121_Validity_Gyro_Rate_Roll.Max = 1.0;
crt_PT_800121_Validity_Gyro_Rate_Roll.DocUnits = '';
crt_PT_800121_Validity_Gyro_Rate_Roll.Dimensions = 1;
crt_PT_800121_Validity_Gyro_Rate_Roll.Complexity = 'real';
crt_PT_800121_Validity_Gyro_Rate_Roll.SampleTime = -1;
crt_PT_800121_Validity_Gyro_Rate_Roll.SamplingMode = 'Sample based';
crt_PT_800121_Validity_Gyro_Rate_Roll.InitialValue = '';
% Signal crt_PT_800121_Accuracy_Gyro_Rates
crt_PT_800121_Accuracy_Gyro_Rates = Simulink.Signal;
crt_PT_800121_Accuracy_Gyro_Rates.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800121_Accuracy_Gyro_Rates.RTWInfo.Alias = '';
crt_PT_800121_Accuracy_Gyro_Rates.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_IMU06_Gyro_Rates, 8388897 (0x800121).' char(10) ...
   'Signal: Accuracy_Gyro_Rates.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800121_Accuracy_Gyro_Rates.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_800121_Accuracy_Gyro_Rates.Min = 0.0;
crt_PT_800121_Accuracy_Gyro_Rates.Max = 0.0;
crt_PT_800121_Accuracy_Gyro_Rates.DocUnits = '';
crt_PT_800121_Accuracy_Gyro_Rates.Dimensions = 1;
crt_PT_800121_Accuracy_Gyro_Rates.Complexity = 'real';
crt_PT_800121_Accuracy_Gyro_Rates.SampleTime = -1;
crt_PT_800121_Accuracy_Gyro_Rates.SamplingMode = 'Sample based';
crt_PT_800121_Accuracy_Gyro_Rates.InitialValue = '';
% Signal crt_PT_800121_Gyro_Rate_Yaw
crt_PT_800121_Gyro_Rate_Yaw = Simulink.Signal;
crt_PT_800121_Gyro_Rate_Yaw.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800121_Gyro_Rate_Yaw.RTWInfo.Alias = '';
crt_PT_800121_Gyro_Rate_Yaw.Description = ...
  ['Yaw rate is positive for clockwise rotation when looking down on the vehicle from above.' char(10) ...
   'Frame: RT_IMU06_Gyro_Rates, 8388897 (0x800121).' char(10) ...
   'Signal: Gyro_Rate_Yaw.' char(10) ...
   'Range (world values): -327.0 ... 327.0 [degrees/s].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees/s]' ...
  ];
crt_PT_800121_Gyro_Rate_Yaw.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_800121_Gyro_Rate_Yaw.Min = -327.0;
crt_PT_800121_Gyro_Rate_Yaw.Max = 327.0;
crt_PT_800121_Gyro_Rate_Yaw.DocUnits = 'degrees/s';
crt_PT_800121_Gyro_Rate_Yaw.Dimensions = 1;
crt_PT_800121_Gyro_Rate_Yaw.Complexity = 'real';
crt_PT_800121_Gyro_Rate_Yaw.SampleTime = -1;
crt_PT_800121_Gyro_Rate_Yaw.SamplingMode = 'Sample based';
crt_PT_800121_Gyro_Rate_Yaw.InitialValue = '';
% Signal crt_PT_800121_Gyro_Rate_Pitch
crt_PT_800121_Gyro_Rate_Pitch = Simulink.Signal;
crt_PT_800121_Gyro_Rate_Pitch.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800121_Gyro_Rate_Pitch.RTWInfo.Alias = '';
crt_PT_800121_Gyro_Rate_Pitch.Description = ...
  ['Pitch rate is positive for clockwise rotation when looking at the left hand side of the vehicle from the left of the vehicle.' char(10) ...
   'Frame: RT_IMU06_Gyro_Rates, 8388897 (0x800121).' char(10) ...
   'Signal: Gyro_Rate_Pitch.' char(10) ...
   'Range (world values): -327.0 ... 327.0 [degrees/s].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees/s]' ...
  ];
crt_PT_800121_Gyro_Rate_Pitch.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_800121_Gyro_Rate_Pitch.Min = -327.0;
crt_PT_800121_Gyro_Rate_Pitch.Max = 327.0;
crt_PT_800121_Gyro_Rate_Pitch.DocUnits = 'degrees/s';
crt_PT_800121_Gyro_Rate_Pitch.Dimensions = 1;
crt_PT_800121_Gyro_Rate_Pitch.Complexity = 'real';
crt_PT_800121_Gyro_Rate_Pitch.SampleTime = -1;
crt_PT_800121_Gyro_Rate_Pitch.SamplingMode = 'Sample based';
crt_PT_800121_Gyro_Rate_Pitch.InitialValue = '';
% Signal crt_PT_800121_Gyro_Rate_Roll
crt_PT_800121_Gyro_Rate_Roll = Simulink.Signal;
crt_PT_800121_Gyro_Rate_Roll.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800121_Gyro_Rate_Roll.RTWInfo.Alias = '';
crt_PT_800121_Gyro_Rate_Roll.Description = ...
  ['Roll rate is positive for clockwise rotation when looking at the rear of the vehicle from behind the vehicle.' char(10) ...
   'Frame: RT_IMU06_Gyro_Rates, 8388897 (0x800121).' char(10) ...
   'Signal: Gyro_Rate_Roll.' char(10) ...
   'Range (world values): -327.0 ... 327.0 [degrees/s].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees/s]' ...
  ];
crt_PT_800121_Gyro_Rate_Roll.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_800121_Gyro_Rate_Roll.Min = -327.0;
crt_PT_800121_Gyro_Rate_Roll.Max = 327.0;
crt_PT_800121_Gyro_Rate_Roll.DocUnits = 'degrees/s';
crt_PT_800121_Gyro_Rate_Roll.Dimensions = 1;
crt_PT_800121_Gyro_Rate_Roll.Complexity = 'real';
crt_PT_800121_Gyro_Rate_Roll.SampleTime = -1;
crt_PT_800121_Gyro_Rate_Roll.SamplingMode = 'Sample based';
crt_PT_800121_Gyro_Rate_Roll.InitialValue = '';

% Frame RT_IMU06_Accel, 8388641 (0x800021)
% Signal crt_PT_800021_Validity_Accel_Longitudinal
crt_PT_800021_Validity_Accel_Longitudinal = Simulink.Signal;
crt_PT_800021_Validity_Accel_Longitudinal.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800021_Validity_Accel_Longitudinal.RTWInfo.Alias = '';
crt_PT_800021_Validity_Accel_Longitudinal.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_IMU06_Accel, 8388641 (0x800021).' char(10) ...
   'Signal: Validity_Accel_Longitudinal.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800021_Validity_Accel_Longitudinal.DataType = 'boolean';
crt_PT_800021_Validity_Accel_Longitudinal.Min = 0.0;
crt_PT_800021_Validity_Accel_Longitudinal.Max = 1.0;
crt_PT_800021_Validity_Accel_Longitudinal.DocUnits = '';
crt_PT_800021_Validity_Accel_Longitudinal.Dimensions = 1;
crt_PT_800021_Validity_Accel_Longitudinal.Complexity = 'real';
crt_PT_800021_Validity_Accel_Longitudinal.SampleTime = -1;
crt_PT_800021_Validity_Accel_Longitudinal.SamplingMode = 'Sample based';
crt_PT_800021_Validity_Accel_Longitudinal.InitialValue = '';
% Signal crt_PT_800021_Validity_Accel_Lateral
crt_PT_800021_Validity_Accel_Lateral = Simulink.Signal;
crt_PT_800021_Validity_Accel_Lateral.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800021_Validity_Accel_Lateral.RTWInfo.Alias = '';
crt_PT_800021_Validity_Accel_Lateral.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_IMU06_Accel, 8388641 (0x800021).' char(10) ...
   'Signal: Validity_Accel_Lateral.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800021_Validity_Accel_Lateral.DataType = 'boolean';
crt_PT_800021_Validity_Accel_Lateral.Min = 0.0;
crt_PT_800021_Validity_Accel_Lateral.Max = 1.0;
crt_PT_800021_Validity_Accel_Lateral.DocUnits = '';
crt_PT_800021_Validity_Accel_Lateral.Dimensions = 1;
crt_PT_800021_Validity_Accel_Lateral.Complexity = 'real';
crt_PT_800021_Validity_Accel_Lateral.SampleTime = -1;
crt_PT_800021_Validity_Accel_Lateral.SamplingMode = 'Sample based';
crt_PT_800021_Validity_Accel_Lateral.InitialValue = '';
% Signal crt_PT_800021_Validity_Accel_Vertical
crt_PT_800021_Validity_Accel_Vertical = Simulink.Signal;
crt_PT_800021_Validity_Accel_Vertical.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800021_Validity_Accel_Vertical.RTWInfo.Alias = '';
crt_PT_800021_Validity_Accel_Vertical.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_IMU06_Accel, 8388641 (0x800021).' char(10) ...
   'Signal: Validity_Accel_Vertical.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800021_Validity_Accel_Vertical.DataType = 'boolean';
crt_PT_800021_Validity_Accel_Vertical.Min = 0.0;
crt_PT_800021_Validity_Accel_Vertical.Max = 1.0;
crt_PT_800021_Validity_Accel_Vertical.DocUnits = '';
crt_PT_800021_Validity_Accel_Vertical.Dimensions = 1;
crt_PT_800021_Validity_Accel_Vertical.Complexity = 'real';
crt_PT_800021_Validity_Accel_Vertical.SampleTime = -1;
crt_PT_800021_Validity_Accel_Vertical.SamplingMode = 'Sample based';
crt_PT_800021_Validity_Accel_Vertical.InitialValue = '';
% Signal crt_PT_800021_Accuracy_Accel
crt_PT_800021_Accuracy_Accel = Simulink.Signal;
crt_PT_800021_Accuracy_Accel.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800021_Accuracy_Accel.RTWInfo.Alias = '';
crt_PT_800021_Accuracy_Accel.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_IMU06_Accel, 8388641 (0x800021).' char(10) ...
   'Signal: Accuracy_Accel.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800021_Accuracy_Accel.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_800021_Accuracy_Accel.Min = 0.0;
crt_PT_800021_Accuracy_Accel.Max = 255.0;
crt_PT_800021_Accuracy_Accel.DocUnits = '';
crt_PT_800021_Accuracy_Accel.Dimensions = 1;
crt_PT_800021_Accuracy_Accel.Complexity = 'real';
crt_PT_800021_Accuracy_Accel.SampleTime = -1;
crt_PT_800021_Accuracy_Accel.SamplingMode = 'Sample based';
crt_PT_800021_Accuracy_Accel.InitialValue = '';
% Signal crt_PT_800021_Accel_Longitudinal
crt_PT_800021_Accel_Longitudinal = Simulink.Signal;
crt_PT_800021_Accel_Longitudinal.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800021_Accel_Longitudinal.RTWInfo.Alias = '';
crt_PT_800021_Accel_Longitudinal.Description = ...
  ['Longitudinal acceleration.  This is positive when the vehicle accelerates in a forwards direction.' char(10) ...
   'Frame: RT_IMU06_Accel, 8388641 (0x800021).' char(10) ...
   'Signal: Accel_Longitudinal.' char(10) ...
   'Range (world values): -65.0 ... 65.0 [g].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [g]' ...
  ];
crt_PT_800021_Accel_Longitudinal.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_800021_Accel_Longitudinal.Min = -65.0;
crt_PT_800021_Accel_Longitudinal.Max = 65.0;
crt_PT_800021_Accel_Longitudinal.DocUnits = 'g';
crt_PT_800021_Accel_Longitudinal.Dimensions = 1;
crt_PT_800021_Accel_Longitudinal.Complexity = 'real';
crt_PT_800021_Accel_Longitudinal.SampleTime = -1;
crt_PT_800021_Accel_Longitudinal.SamplingMode = 'Sample based';
crt_PT_800021_Accel_Longitudinal.InitialValue = '';
% Signal crt_PT_800021_Accel_Lateral
crt_PT_800021_Accel_Lateral = Simulink.Signal;
crt_PT_800021_Accel_Lateral.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800021_Accel_Lateral.RTWInfo.Alias = '';
crt_PT_800021_Accel_Lateral.Description = ...
  ['Lateral acceleration.  This is positive when the vehicle accelerates towards the right, e.g. when cornering around a right-hand bend.' char(10) ...
   'Frame: RT_IMU06_Accel, 8388641 (0x800021).' char(10) ...
   'Signal: Accel_Lateral.' char(10) ...
   'Range (world values): -65.0 ... 65.0 [g].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [g]' ...
  ];
crt_PT_800021_Accel_Lateral.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_800021_Accel_Lateral.Min = -65.0;
crt_PT_800021_Accel_Lateral.Max = 65.0;
crt_PT_800021_Accel_Lateral.DocUnits = 'g';
crt_PT_800021_Accel_Lateral.Dimensions = 1;
crt_PT_800021_Accel_Lateral.Complexity = 'real';
crt_PT_800021_Accel_Lateral.SampleTime = -1;
crt_PT_800021_Accel_Lateral.SamplingMode = 'Sample based';
crt_PT_800021_Accel_Lateral.InitialValue = '';
% Signal crt_PT_800021_Accel_Vertical
crt_PT_800021_Accel_Vertical = Simulink.Signal;
crt_PT_800021_Accel_Vertical.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800021_Accel_Vertical.RTWInfo.Alias = '';
crt_PT_800021_Accel_Vertical.Description = ...
  ['Vertical acceleration.  This is positive when the vehicle accelerates in an upwards direction, e.g. when travelling through a dip.' char(10) ...
   'Frame: RT_IMU06_Accel, 8388641 (0x800021).' char(10) ...
   'Signal: Accel_Vertical.' char(10) ...
   'Range (world values): -65.0 ... 65.0 [g].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [g]' ...
  ];
crt_PT_800021_Accel_Vertical.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_800021_Accel_Vertical.Min = -65.0;
crt_PT_800021_Accel_Vertical.Max = 65.0;
crt_PT_800021_Accel_Vertical.DocUnits = 'g';
crt_PT_800021_Accel_Vertical.Dimensions = 1;
crt_PT_800021_Accel_Vertical.Complexity = 'real';
crt_PT_800021_Accel_Vertical.SampleTime = -1;
crt_PT_800021_Accel_Vertical.SamplingMode = 'Sample based';
crt_PT_800021_Accel_Vertical.InitialValue = '';

% Frame RT_SB_Speed, 8392738 (0x801022)
% Signal crt_PT_801022_Validity_Speed
crt_PT_801022_Validity_Speed = Simulink.Signal;
crt_PT_801022_Validity_Speed.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_801022_Validity_Speed.RTWInfo.Alias = '';
crt_PT_801022_Validity_Speed.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Speed, 8392738 (0x801022).' char(10) ...
   'Signal: Validity_Speed.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_801022_Validity_Speed.DataType = 'boolean';
crt_PT_801022_Validity_Speed.Min = 0.0;
crt_PT_801022_Validity_Speed.Max = 1.0;
crt_PT_801022_Validity_Speed.DocUnits = '';
crt_PT_801022_Validity_Speed.Dimensions = 1;
crt_PT_801022_Validity_Speed.Complexity = 'real';
crt_PT_801022_Validity_Speed.SampleTime = -1;
crt_PT_801022_Validity_Speed.SamplingMode = 'Sample based';
crt_PT_801022_Validity_Speed.InitialValue = '';
% Signal crt_PT_801022_Accuracy_Speed
crt_PT_801022_Accuracy_Speed = Simulink.Signal;
crt_PT_801022_Accuracy_Speed.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_801022_Accuracy_Speed.RTWInfo.Alias = '';
crt_PT_801022_Accuracy_Speed.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_Speed, 8392738 (0x801022).' char(10) ...
   'Signal: Accuracy_Speed.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_801022_Accuracy_Speed.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_801022_Accuracy_Speed.Min = 0.0;
crt_PT_801022_Accuracy_Speed.Max = 255.0;
crt_PT_801022_Accuracy_Speed.DocUnits = '';
crt_PT_801022_Accuracy_Speed.Dimensions = 1;
crt_PT_801022_Accuracy_Speed.Complexity = 'real';
crt_PT_801022_Accuracy_Speed.SampleTime = -1;
crt_PT_801022_Accuracy_Speed.SamplingMode = 'Sample based';
crt_PT_801022_Accuracy_Speed.InitialValue = '';
% Signal crt_PT_801022_Speed
crt_PT_801022_Speed = Simulink.Signal;
crt_PT_801022_Speed.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_801022_Speed.RTWInfo.Alias = '';
crt_PT_801022_Speed.Description = ...
  ['Frame: RT_SB_Speed, 8392738 (0x801022).' char(10) ...
   'Signal: Speed.' char(10) ...
   'Range (world values): -20000.0 ... 20000.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-5*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_801022_Speed.DataType = 'fixdt(1, 32, 1.0E-5, 0.0)';
crt_PT_801022_Speed.Min = -20000.0;
crt_PT_801022_Speed.Max = 20000.0;
crt_PT_801022_Speed.DocUnits = 'm/s';
crt_PT_801022_Speed.Dimensions = 1;
crt_PT_801022_Speed.Complexity = 'real';
crt_PT_801022_Speed.SampleTime = -1;
crt_PT_801022_Speed.SamplingMode = 'Sample based';
crt_PT_801022_Speed.InitialValue = '';

% Frame RT_SB_RTK_Slip, 9183522 (0x8c2122)
% Signal crt_PT_8c2122_Validity_RTK_Slip
crt_PT_8c2122_Validity_RTK_Slip = Simulink.Signal;
crt_PT_8c2122_Validity_RTK_Slip.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c2122_Validity_RTK_Slip.RTWInfo.Alias = '';
crt_PT_8c2122_Validity_RTK_Slip.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_RTK_Slip, 9183522 (0x8c2122).' char(10) ...
   'Signal: Validity_RTK_Slip.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c2122_Validity_RTK_Slip.DataType = 'boolean';
crt_PT_8c2122_Validity_RTK_Slip.Min = 0.0;
crt_PT_8c2122_Validity_RTK_Slip.Max = 1.0;
crt_PT_8c2122_Validity_RTK_Slip.DocUnits = '';
crt_PT_8c2122_Validity_RTK_Slip.Dimensions = 1;
crt_PT_8c2122_Validity_RTK_Slip.Complexity = 'real';
crt_PT_8c2122_Validity_RTK_Slip.SampleTime = -1;
crt_PT_8c2122_Validity_RTK_Slip.SamplingMode = 'Sample based';
crt_PT_8c2122_Validity_RTK_Slip.InitialValue = '';
% Signal crt_PT_8c2122_Validity_RTK_Squat
crt_PT_8c2122_Validity_RTK_Squat = Simulink.Signal;
crt_PT_8c2122_Validity_RTK_Squat.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c2122_Validity_RTK_Squat.RTWInfo.Alias = '';
crt_PT_8c2122_Validity_RTK_Squat.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_RTK_Slip, 9183522 (0x8c2122).' char(10) ...
   'Signal: Validity_RTK_Squat.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c2122_Validity_RTK_Squat.DataType = 'boolean';
crt_PT_8c2122_Validity_RTK_Squat.Min = 0.0;
crt_PT_8c2122_Validity_RTK_Squat.Max = 1.0;
crt_PT_8c2122_Validity_RTK_Squat.DocUnits = '';
crt_PT_8c2122_Validity_RTK_Squat.Dimensions = 1;
crt_PT_8c2122_Validity_RTK_Squat.Complexity = 'real';
crt_PT_8c2122_Validity_RTK_Squat.SampleTime = -1;
crt_PT_8c2122_Validity_RTK_Squat.SamplingMode = 'Sample based';
crt_PT_8c2122_Validity_RTK_Squat.InitialValue = '';
% Signal crt_PT_8c2122_Validity_RTK_Baseline
crt_PT_8c2122_Validity_RTK_Baseline = Simulink.Signal;
crt_PT_8c2122_Validity_RTK_Baseline.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c2122_Validity_RTK_Baseline.RTWInfo.Alias = '';
crt_PT_8c2122_Validity_RTK_Baseline.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_RTK_Slip, 9183522 (0x8c2122).' char(10) ...
   'Signal: Validity_RTK_Baseline.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c2122_Validity_RTK_Baseline.DataType = 'boolean';
crt_PT_8c2122_Validity_RTK_Baseline.Min = 0.0;
crt_PT_8c2122_Validity_RTK_Baseline.Max = 1.0;
crt_PT_8c2122_Validity_RTK_Baseline.DocUnits = '';
crt_PT_8c2122_Validity_RTK_Baseline.Dimensions = 1;
crt_PT_8c2122_Validity_RTK_Baseline.Complexity = 'real';
crt_PT_8c2122_Validity_RTK_Baseline.SampleTime = -1;
crt_PT_8c2122_Validity_RTK_Baseline.SamplingMode = 'Sample based';
crt_PT_8c2122_Validity_RTK_Baseline.InitialValue = '';
% Signal crt_PT_8c2122_Accuracy_RTK_Baseline
crt_PT_8c2122_Accuracy_RTK_Baseline = Simulink.Signal;
crt_PT_8c2122_Accuracy_RTK_Baseline.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c2122_Accuracy_RTK_Baseline.RTWInfo.Alias = '';
crt_PT_8c2122_Accuracy_RTK_Baseline.Description = ...
  ['Frame: RT_SB_RTK_Slip, 9183522 (0x8c2122).' char(10) ...
   'Signal: Accuracy_RTK_Baseline.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c2122_Accuracy_RTK_Baseline.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c2122_Accuracy_RTK_Baseline.Min = 0.0;
crt_PT_8c2122_Accuracy_RTK_Baseline.Max = 255.0;
crt_PT_8c2122_Accuracy_RTK_Baseline.DocUnits = '';
crt_PT_8c2122_Accuracy_RTK_Baseline.Dimensions = 1;
crt_PT_8c2122_Accuracy_RTK_Baseline.Complexity = 'real';
crt_PT_8c2122_Accuracy_RTK_Baseline.SampleTime = -1;
crt_PT_8c2122_Accuracy_RTK_Baseline.SamplingMode = 'Sample based';
crt_PT_8c2122_Accuracy_RTK_Baseline.InitialValue = '';
% Signal crt_PT_8c2122_RTK_Slip
crt_PT_8c2122_RTK_Slip = Simulink.Signal;
crt_PT_8c2122_RTK_Slip.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c2122_RTK_Slip.RTWInfo.Alias = '';
crt_PT_8c2122_RTK_Slip.Description = ...
  ['Slip is defined as the difference between yaw and heading.' char(10) ...
   'Frame: RT_SB_RTK_Slip, 9183522 (0x8c2122).' char(10) ...
   'Signal: RTK_Slip.' char(10) ...
   'Range (world values): -360.0 ... 360.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8c2122_RTK_Slip.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8c2122_RTK_Slip.Min = -360.0;
crt_PT_8c2122_RTK_Slip.Max = 360.0;
crt_PT_8c2122_RTK_Slip.DocUnits = 'degrees';
crt_PT_8c2122_RTK_Slip.Dimensions = 1;
crt_PT_8c2122_RTK_Slip.Complexity = 'real';
crt_PT_8c2122_RTK_Slip.SampleTime = -1;
crt_PT_8c2122_RTK_Slip.SamplingMode = 'Sample based';
crt_PT_8c2122_RTK_Slip.InitialValue = '';
% Signal crt_PT_8c2122_RTK_Squat
crt_PT_8c2122_RTK_Squat = Simulink.Signal;
crt_PT_8c2122_RTK_Squat.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c2122_RTK_Squat.RTWInfo.Alias = '';
crt_PT_8c2122_RTK_Squat.Description = ...
  ['Squat is defined as the difference between pitch and gradient.' char(10) ...
   'Frame: RT_SB_RTK_Slip, 9183522 (0x8c2122).' char(10) ...
   'Signal: RTK_Squat.' char(10) ...
   'Range (world values): -360.0 ... 360.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8c2122_RTK_Squat.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8c2122_RTK_Squat.Min = -360.0;
crt_PT_8c2122_RTK_Squat.Max = 360.0;
crt_PT_8c2122_RTK_Squat.DocUnits = 'degrees';
crt_PT_8c2122_RTK_Squat.Dimensions = 1;
crt_PT_8c2122_RTK_Squat.Complexity = 'real';
crt_PT_8c2122_RTK_Squat.SampleTime = -1;
crt_PT_8c2122_RTK_Squat.SamplingMode = 'Sample based';
crt_PT_8c2122_RTK_Squat.InitialValue = '';
% Signal crt_PT_8c2122_RTK_Baseline
crt_PT_8c2122_RTK_Baseline = Simulink.Signal;
crt_PT_8c2122_RTK_Baseline.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c2122_RTK_Baseline.RTWInfo.Alias = '';
crt_PT_8c2122_RTK_Baseline.Description = ...
  ['This is the estimated baseline length calculated by the RTK solution.' char(10) ...
   'Frame: RT_SB_RTK_Slip, 9183522 (0x8c2122).' char(10) ...
   'Signal: RTK_Baseline.' char(10) ...
   'Range (world values): 0.0 ... 65535.0 [mm].' char(10) ...
   'Scaling: WorldValue = BinaryValue [mm]' ...
  ];
crt_PT_8c2122_RTK_Baseline.DataType = 'fixdt(0, 16, 1.0, 0.0)';
crt_PT_8c2122_RTK_Baseline.Min = 0.0;
crt_PT_8c2122_RTK_Baseline.Max = 65535.0;
crt_PT_8c2122_RTK_Baseline.DocUnits = 'mm';
crt_PT_8c2122_RTK_Baseline.Dimensions = 1;
crt_PT_8c2122_RTK_Baseline.Complexity = 'real';
crt_PT_8c2122_RTK_Baseline.SampleTime = -1;
crt_PT_8c2122_RTK_Baseline.SamplingMode = 'Sample based';
crt_PT_8c2122_RTK_Baseline.InitialValue = '';

% Frame RT_SB_RTK_Attitude, 9183266 (0x8c2022)
% Signal crt_PT_8c2022_Validity_RTK_Yaw
crt_PT_8c2022_Validity_RTK_Yaw = Simulink.Signal;
crt_PT_8c2022_Validity_RTK_Yaw.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c2022_Validity_RTK_Yaw.RTWInfo.Alias = '';
crt_PT_8c2022_Validity_RTK_Yaw.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_RTK_Attitude, 9183266 (0x8c2022).' char(10) ...
   'Signal: Validity_RTK_Yaw.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c2022_Validity_RTK_Yaw.DataType = 'boolean';
crt_PT_8c2022_Validity_RTK_Yaw.Min = 0.0;
crt_PT_8c2022_Validity_RTK_Yaw.Max = 1.0;
crt_PT_8c2022_Validity_RTK_Yaw.DocUnits = '';
crt_PT_8c2022_Validity_RTK_Yaw.Dimensions = 1;
crt_PT_8c2022_Validity_RTK_Yaw.Complexity = 'real';
crt_PT_8c2022_Validity_RTK_Yaw.SampleTime = -1;
crt_PT_8c2022_Validity_RTK_Yaw.SamplingMode = 'Sample based';
crt_PT_8c2022_Validity_RTK_Yaw.InitialValue = '';
% Signal crt_PT_8c2022_Validity_RTK_Pitch
crt_PT_8c2022_Validity_RTK_Pitch = Simulink.Signal;
crt_PT_8c2022_Validity_RTK_Pitch.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c2022_Validity_RTK_Pitch.RTWInfo.Alias = '';
crt_PT_8c2022_Validity_RTK_Pitch.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_RTK_Attitude, 9183266 (0x8c2022).' char(10) ...
   'Signal: Validity_RTK_Pitch.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c2022_Validity_RTK_Pitch.DataType = 'boolean';
crt_PT_8c2022_Validity_RTK_Pitch.Min = 0.0;
crt_PT_8c2022_Validity_RTK_Pitch.Max = 1.0;
crt_PT_8c2022_Validity_RTK_Pitch.DocUnits = '';
crt_PT_8c2022_Validity_RTK_Pitch.Dimensions = 1;
crt_PT_8c2022_Validity_RTK_Pitch.Complexity = 'real';
crt_PT_8c2022_Validity_RTK_Pitch.SampleTime = -1;
crt_PT_8c2022_Validity_RTK_Pitch.SamplingMode = 'Sample based';
crt_PT_8c2022_Validity_RTK_Pitch.InitialValue = '';
% Signal crt_PT_8c2022_Validity_RTK_Roll
crt_PT_8c2022_Validity_RTK_Roll = Simulink.Signal;
crt_PT_8c2022_Validity_RTK_Roll.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c2022_Validity_RTK_Roll.RTWInfo.Alias = '';
crt_PT_8c2022_Validity_RTK_Roll.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_RTK_Attitude, 9183266 (0x8c2022).' char(10) ...
   'Signal: Validity_RTK_Roll.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c2022_Validity_RTK_Roll.DataType = 'boolean';
crt_PT_8c2022_Validity_RTK_Roll.Min = 0.0;
crt_PT_8c2022_Validity_RTK_Roll.Max = 1.0;
crt_PT_8c2022_Validity_RTK_Roll.DocUnits = '';
crt_PT_8c2022_Validity_RTK_Roll.Dimensions = 1;
crt_PT_8c2022_Validity_RTK_Roll.Complexity = 'real';
crt_PT_8c2022_Validity_RTK_Roll.SampleTime = -1;
crt_PT_8c2022_Validity_RTK_Roll.SamplingMode = 'Sample based';
crt_PT_8c2022_Validity_RTK_Roll.InitialValue = '';
% Signal crt_PT_8c2022_Accuracy_RTK_Attitude
crt_PT_8c2022_Accuracy_RTK_Attitude = Simulink.Signal;
crt_PT_8c2022_Accuracy_RTK_Attitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c2022_Accuracy_RTK_Attitude.RTWInfo.Alias = '';
crt_PT_8c2022_Accuracy_RTK_Attitude.Description = ...
  ['Note that RTK yaw is typically up to about 4 times more accurate than RTK pitch or roll.' char(10) ...
   'Frame: RT_SB_RTK_Attitude, 9183266 (0x8c2022).' char(10) ...
   'Signal: Accuracy_RTK_Attitude.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c2022_Accuracy_RTK_Attitude.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c2022_Accuracy_RTK_Attitude.Min = 0.0;
crt_PT_8c2022_Accuracy_RTK_Attitude.Max = 255.0;
crt_PT_8c2022_Accuracy_RTK_Attitude.DocUnits = '';
crt_PT_8c2022_Accuracy_RTK_Attitude.Dimensions = 1;
crt_PT_8c2022_Accuracy_RTK_Attitude.Complexity = 'real';
crt_PT_8c2022_Accuracy_RTK_Attitude.SampleTime = -1;
crt_PT_8c2022_Accuracy_RTK_Attitude.SamplingMode = 'Sample based';
crt_PT_8c2022_Accuracy_RTK_Attitude.InitialValue = '';
% Signal crt_PT_8c2022_RTK_Attitude_Yaw
crt_PT_8c2022_RTK_Attitude_Yaw = Simulink.Signal;
crt_PT_8c2022_RTK_Attitude_Yaw.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c2022_RTK_Attitude_Yaw.RTWInfo.Alias = '';
crt_PT_8c2022_RTK_Attitude_Yaw.Description = ...
  ['RTK attitude is determined from the MB-RTK solution only.  Yaw is positive for a clockwise rotational displacement from due North, looking down on the vehicle from above.' char(10) ...
   'Frame: RT_SB_RTK_Attitude, 9183266 (0x8c2022).' char(10) ...
   'Signal: RTK_Attitude_Yaw.' char(10) ...
   'Range (world values): -360.0 ... 360.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8c2022_RTK_Attitude_Yaw.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8c2022_RTK_Attitude_Yaw.Min = -360.0;
crt_PT_8c2022_RTK_Attitude_Yaw.Max = 360.0;
crt_PT_8c2022_RTK_Attitude_Yaw.DocUnits = 'degrees';
crt_PT_8c2022_RTK_Attitude_Yaw.Dimensions = 1;
crt_PT_8c2022_RTK_Attitude_Yaw.Complexity = 'real';
crt_PT_8c2022_RTK_Attitude_Yaw.SampleTime = -1;
crt_PT_8c2022_RTK_Attitude_Yaw.SamplingMode = 'Sample based';
crt_PT_8c2022_RTK_Attitude_Yaw.InitialValue = '';
% Signal crt_PT_8c2022_RTK_Attitude_Pitch
crt_PT_8c2022_RTK_Attitude_Pitch = Simulink.Signal;
crt_PT_8c2022_RTK_Attitude_Pitch.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c2022_RTK_Attitude_Pitch.RTWInfo.Alias = '';
crt_PT_8c2022_RTK_Attitude_Pitch.Description = ...
  ['RTK attitude is determined from the MB-RTK solution only.  Pitch is positive for a clockwise rotational displacement from the local horizontal plane when looking at the vehicle from the left hand side of it.' char(10) ...
   'Frame: RT_SB_RTK_Attitude, 9183266 (0x8c2022).' char(10) ...
   'Signal: RTK_Attitude_Pitch.' char(10) ...
   'Range (world values): -90.0 ... 90.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8c2022_RTK_Attitude_Pitch.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8c2022_RTK_Attitude_Pitch.Min = -90.0;
crt_PT_8c2022_RTK_Attitude_Pitch.Max = 90.0;
crt_PT_8c2022_RTK_Attitude_Pitch.DocUnits = 'degrees';
crt_PT_8c2022_RTK_Attitude_Pitch.Dimensions = 1;
crt_PT_8c2022_RTK_Attitude_Pitch.Complexity = 'real';
crt_PT_8c2022_RTK_Attitude_Pitch.SampleTime = -1;
crt_PT_8c2022_RTK_Attitude_Pitch.SamplingMode = 'Sample based';
crt_PT_8c2022_RTK_Attitude_Pitch.InitialValue = '';
% Signal crt_PT_8c2022_RTK_Attitude_Roll
crt_PT_8c2022_RTK_Attitude_Roll = Simulink.Signal;
crt_PT_8c2022_RTK_Attitude_Roll.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c2022_RTK_Attitude_Roll.RTWInfo.Alias = '';
crt_PT_8c2022_RTK_Attitude_Roll.Description = ...
  ['RTK attitude is determined from the MB-RTK solution only.  Roll is positive for a clockwise rotational displacement relative to the local horizontal plane when looking at the vehicle from the rear of it.' char(10) ...
   'Frame: RT_SB_RTK_Attitude, 9183266 (0x8c2022).' char(10) ...
   'Signal: RTK_Attitude_Roll.' char(10) ...
   'Range (world values): -90.0 ... 90.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8c2022_RTK_Attitude_Roll.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8c2022_RTK_Attitude_Roll.Min = -90.0;
crt_PT_8c2022_RTK_Attitude_Roll.Max = 90.0;
crt_PT_8c2022_RTK_Attitude_Roll.DocUnits = 'degrees';
crt_PT_8c2022_RTK_Attitude_Roll.Dimensions = 1;
crt_PT_8c2022_RTK_Attitude_Roll.Complexity = 'real';
crt_PT_8c2022_RTK_Attitude_Roll.SampleTime = -1;
crt_PT_8c2022_RTK_Attitude_Roll.SamplingMode = 'Sample based';
crt_PT_8c2022_RTK_Attitude_Roll.InitialValue = '';

% Frame RT_SB_GPS_Mcycle_Lean, 9187362 (0x8c3022)
% Signal crt_PT_8c3022_Validity_GPS_Lateral_Accel
crt_PT_8c3022_Validity_GPS_Lateral_Accel = Simulink.Signal;
crt_PT_8c3022_Validity_GPS_Lateral_Accel.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c3022_Validity_GPS_Lateral_Accel.RTWInfo.Alias = '';
crt_PT_8c3022_Validity_GPS_Lateral_Accel.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Mcycle_Lean, 9187362 (0x8c3022).' char(10) ...
   'Signal: Validity_GPS_Lateral_Accel.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c3022_Validity_GPS_Lateral_Accel.DataType = 'boolean';
crt_PT_8c3022_Validity_GPS_Lateral_Accel.Min = 0.0;
crt_PT_8c3022_Validity_GPS_Lateral_Accel.Max = 1.0;
crt_PT_8c3022_Validity_GPS_Lateral_Accel.DocUnits = '';
crt_PT_8c3022_Validity_GPS_Lateral_Accel.Dimensions = 1;
crt_PT_8c3022_Validity_GPS_Lateral_Accel.Complexity = 'real';
crt_PT_8c3022_Validity_GPS_Lateral_Accel.SampleTime = -1;
crt_PT_8c3022_Validity_GPS_Lateral_Accel.SamplingMode = 'Sample based';
crt_PT_8c3022_Validity_GPS_Lateral_Accel.InitialValue = '';
% Signal crt_PT_8c3022_Validity_GPS_Mcycle_Lean
crt_PT_8c3022_Validity_GPS_Mcycle_Lean = Simulink.Signal;
crt_PT_8c3022_Validity_GPS_Mcycle_Lean.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c3022_Validity_GPS_Mcycle_Lean.RTWInfo.Alias = '';
crt_PT_8c3022_Validity_GPS_Mcycle_Lean.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Mcycle_Lean, 9187362 (0x8c3022).' char(10) ...
   'Signal: Validity_GPS_Mcycle_Lean.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c3022_Validity_GPS_Mcycle_Lean.DataType = 'boolean';
crt_PT_8c3022_Validity_GPS_Mcycle_Lean.Min = 0.0;
crt_PT_8c3022_Validity_GPS_Mcycle_Lean.Max = 1.0;
crt_PT_8c3022_Validity_GPS_Mcycle_Lean.DocUnits = '';
crt_PT_8c3022_Validity_GPS_Mcycle_Lean.Dimensions = 1;
crt_PT_8c3022_Validity_GPS_Mcycle_Lean.Complexity = 'real';
crt_PT_8c3022_Validity_GPS_Mcycle_Lean.SampleTime = -1;
crt_PT_8c3022_Validity_GPS_Mcycle_Lean.SamplingMode = 'Sample based';
crt_PT_8c3022_Validity_GPS_Mcycle_Lean.InitialValue = '';
% Signal crt_PT_8c3022_Accuracy_GPS_Lateral_Accel
crt_PT_8c3022_Accuracy_GPS_Lateral_Accel = Simulink.Signal;
crt_PT_8c3022_Accuracy_GPS_Lateral_Accel.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c3022_Accuracy_GPS_Lateral_Accel.RTWInfo.Alias = '';
crt_PT_8c3022_Accuracy_GPS_Lateral_Accel.Description = ...
  ['This accuracy value applies to both GPS-derived lateral acceleration and motorcycle lean angle, since both are derived from the rate of change of GPS heading.' char(10) ...
   'Frame: RT_SB_GPS_Mcycle_Lean, 9187362 (0x8c3022).' char(10) ...
   'Signal: Accuracy_GPS_Lateral_Accel.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c3022_Accuracy_GPS_Lateral_Accel.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c3022_Accuracy_GPS_Lateral_Accel.Min = 0.0;
crt_PT_8c3022_Accuracy_GPS_Lateral_Accel.Max = 255.0;
crt_PT_8c3022_Accuracy_GPS_Lateral_Accel.DocUnits = '';
crt_PT_8c3022_Accuracy_GPS_Lateral_Accel.Dimensions = 1;
crt_PT_8c3022_Accuracy_GPS_Lateral_Accel.Complexity = 'real';
crt_PT_8c3022_Accuracy_GPS_Lateral_Accel.SampleTime = -1;
crt_PT_8c3022_Accuracy_GPS_Lateral_Accel.SamplingMode = 'Sample based';
crt_PT_8c3022_Accuracy_GPS_Lateral_Accel.InitialValue = '';
% Signal crt_PT_8c3022_GPS_Lateral_Accel
crt_PT_8c3022_GPS_Lateral_Accel = Simulink.Signal;
crt_PT_8c3022_GPS_Lateral_Accel.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c3022_GPS_Lateral_Accel.RTWInfo.Alias = '';
crt_PT_8c3022_GPS_Lateral_Accel.Description = ...
  ['GPS-derived lateral acceleration.  This is derived by differentiating GPS heading - it is much more noisy than lateral accel from the accelerometers, but useful for m/cycle applications.' char(10) ...
   'Frame: RT_SB_GPS_Mcycle_Lean, 9187362 (0x8c3022).' char(10) ...
   'Signal: GPS_Lateral_Accel.' char(10) ...
   'Range (world values): -65.0 ... 65.0 [g].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [g]' ...
  ];
crt_PT_8c3022_GPS_Lateral_Accel.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_8c3022_GPS_Lateral_Accel.Min = -65.0;
crt_PT_8c3022_GPS_Lateral_Accel.Max = 65.0;
crt_PT_8c3022_GPS_Lateral_Accel.DocUnits = 'g';
crt_PT_8c3022_GPS_Lateral_Accel.Dimensions = 1;
crt_PT_8c3022_GPS_Lateral_Accel.Complexity = 'real';
crt_PT_8c3022_GPS_Lateral_Accel.SampleTime = -1;
crt_PT_8c3022_GPS_Lateral_Accel.SamplingMode = 'Sample based';
crt_PT_8c3022_GPS_Lateral_Accel.InitialValue = '';
% Signal crt_PT_8c3022_GPS_Mcycle_Lean_Angle
crt_PT_8c3022_GPS_Mcycle_Lean_Angle = Simulink.Signal;
crt_PT_8c3022_GPS_Mcycle_Lean_Angle.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c3022_GPS_Mcycle_Lean_Angle.RTWInfo.Alias = '';
crt_PT_8c3022_GPS_Mcycle_Lean_Angle.Description = ...
  ['Motorcycle lean angle, derived from rate of change of heading from GPS.  This is the lean angle of the centre of mass of the combined bike + rider.' char(10) ...
   'Frame: RT_SB_GPS_Mcycle_Lean, 9187362 (0x8c3022).' char(10) ...
   'Signal: GPS_Mcycle_Lean_Angle.' char(10) ...
   'Range (world values): -90.0 ... 90.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8c3022_GPS_Mcycle_Lean_Angle.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8c3022_GPS_Mcycle_Lean_Angle.Min = -90.0;
crt_PT_8c3022_GPS_Mcycle_Lean_Angle.Max = 90.0;
crt_PT_8c3022_GPS_Mcycle_Lean_Angle.DocUnits = 'degrees';
crt_PT_8c3022_GPS_Mcycle_Lean_Angle.Dimensions = 1;
crt_PT_8c3022_GPS_Mcycle_Lean_Angle.Complexity = 'real';
crt_PT_8c3022_GPS_Mcycle_Lean_Angle.SampleTime = -1;
crt_PT_8c3022_GPS_Mcycle_Lean_Angle.SamplingMode = 'Sample based';
crt_PT_8c3022_GPS_Mcycle_Lean_Angle.InitialValue = '';

% Frame RT_SB_GPS_Status, 9175074 (0x8c0022)
% Signal crt_PT_8c0022_GPS_Status
crt_PT_8c0022_GPS_Status = Simulink.Signal;
crt_PT_8c0022_GPS_Status.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0022_GPS_Status.RTWInfo.Alias = '';
crt_PT_8c0022_GPS_Status.Description = ...
  ['Frame: RT_SB_GPS_Status, 9175074 (0x8c0022).' char(10) ...
   'Signal: GPS_Status.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0022_GPS_Status.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0022_GPS_Status.Min = 0.0;
crt_PT_8c0022_GPS_Status.Max = 255.0;
crt_PT_8c0022_GPS_Status.DocUnits = '';
crt_PT_8c0022_GPS_Status.Dimensions = 1;
crt_PT_8c0022_GPS_Status.Complexity = 'real';
crt_PT_8c0022_GPS_Status.SampleTime = -1;
crt_PT_8c0022_GPS_Status.SamplingMode = 'Sample based';
crt_PT_8c0022_GPS_Status.InitialValue = '';
% Signal crt_PT_8c0022_Firmware_Version_Major
crt_PT_8c0022_Firmware_Version_Major = Simulink.Signal;
crt_PT_8c0022_Firmware_Version_Major.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0022_Firmware_Version_Major.RTWInfo.Alias = '';
crt_PT_8c0022_Firmware_Version_Major.Description = ...
  ['Frame: RT_SB_GPS_Status, 9175074 (0x8c0022).' char(10) ...
   'Signal: Firmware_Version_Major.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0022_Firmware_Version_Major.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0022_Firmware_Version_Major.Min = 0.0;
crt_PT_8c0022_Firmware_Version_Major.Max = 255.0;
crt_PT_8c0022_Firmware_Version_Major.DocUnits = '';
crt_PT_8c0022_Firmware_Version_Major.Dimensions = 1;
crt_PT_8c0022_Firmware_Version_Major.Complexity = 'real';
crt_PT_8c0022_Firmware_Version_Major.SampleTime = -1;
crt_PT_8c0022_Firmware_Version_Major.SamplingMode = 'Sample based';
crt_PT_8c0022_Firmware_Version_Major.InitialValue = '';
% Signal crt_PT_8c0022_Firmware_Version_Intermediate
crt_PT_8c0022_Firmware_Version_Intermediate = Simulink.Signal;
crt_PT_8c0022_Firmware_Version_Intermediate.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0022_Firmware_Version_Intermediate.RTWInfo.Alias = '';
crt_PT_8c0022_Firmware_Version_Intermediate.Description = ...
  ['Frame: RT_SB_GPS_Status, 9175074 (0x8c0022).' char(10) ...
   'Signal: Firmware_Version_Intermediate.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0022_Firmware_Version_Intermediate.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0022_Firmware_Version_Intermediate.Min = 0.0;
crt_PT_8c0022_Firmware_Version_Intermediate.Max = 255.0;
crt_PT_8c0022_Firmware_Version_Intermediate.DocUnits = '';
crt_PT_8c0022_Firmware_Version_Intermediate.Dimensions = 1;
crt_PT_8c0022_Firmware_Version_Intermediate.Complexity = 'real';
crt_PT_8c0022_Firmware_Version_Intermediate.SampleTime = -1;
crt_PT_8c0022_Firmware_Version_Intermediate.SamplingMode = 'Sample based';
crt_PT_8c0022_Firmware_Version_Intermediate.InitialValue = '';
% Signal crt_PT_8c0022_Firmware_Version_Minor
crt_PT_8c0022_Firmware_Version_Minor = Simulink.Signal;
crt_PT_8c0022_Firmware_Version_Minor.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0022_Firmware_Version_Minor.RTWInfo.Alias = '';
crt_PT_8c0022_Firmware_Version_Minor.Description = ...
  ['Frame: RT_SB_GPS_Status, 9175074 (0x8c0022).' char(10) ...
   'Signal: Firmware_Version_Minor.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0022_Firmware_Version_Minor.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0022_Firmware_Version_Minor.Min = 0.0;
crt_PT_8c0022_Firmware_Version_Minor.Max = 255.0;
crt_PT_8c0022_Firmware_Version_Minor.DocUnits = '';
crt_PT_8c0022_Firmware_Version_Minor.Dimensions = 1;
crt_PT_8c0022_Firmware_Version_Minor.Complexity = 'real';
crt_PT_8c0022_Firmware_Version_Minor.SampleTime = -1;
crt_PT_8c0022_Firmware_Version_Minor.SamplingMode = 'Sample based';
crt_PT_8c0022_Firmware_Version_Minor.InitialValue = '';
% Signal crt_PT_8c0022_GPS_nSv
crt_PT_8c0022_GPS_nSv = Simulink.Signal;
crt_PT_8c0022_GPS_nSv.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0022_GPS_nSv.RTWInfo.Alias = '';
crt_PT_8c0022_GPS_nSv.Description = ...
  ['Number of satellites used in GPS solution' char(10) ...
   'Frame: RT_SB_GPS_Status, 9175074 (0x8c0022).' char(10) ...
   'Signal: GPS_nSv.' char(10) ...
   'Range (world values): 0.0 ... 16.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0022_GPS_nSv.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0022_GPS_nSv.Min = 0.0;
crt_PT_8c0022_GPS_nSv.Max = 16.0;
crt_PT_8c0022_GPS_nSv.DocUnits = '';
crt_PT_8c0022_GPS_nSv.Dimensions = 1;
crt_PT_8c0022_GPS_nSv.Complexity = 'real';
crt_PT_8c0022_GPS_nSv.SampleTime = -1;
crt_PT_8c0022_GPS_nSv.SamplingMode = 'Sample based';
crt_PT_8c0022_GPS_nSv.InitialValue = '';
% Signal crt_PT_8c0022_GPS_nSv_2
crt_PT_8c0022_GPS_nSv_2 = Simulink.Signal;
crt_PT_8c0022_GPS_nSv_2.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0022_GPS_nSv_2.RTWInfo.Alias = '';
crt_PT_8c0022_GPS_nSv_2.Description = ...
  ['Number of satellites used in GPS solution by module 2 on RTK units...' char(10) ...
   'Frame: RT_SB_GPS_Status, 9175074 (0x8c0022).' char(10) ...
   'Signal: GPS_nSv_2.' char(10) ...
   'Range (world values): 0.0 ... 16.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0022_GPS_nSv_2.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0022_GPS_nSv_2.Min = 0.0;
crt_PT_8c0022_GPS_nSv_2.Max = 16.0;
crt_PT_8c0022_GPS_nSv_2.DocUnits = '';
crt_PT_8c0022_GPS_nSv_2.Dimensions = 1;
crt_PT_8c0022_GPS_nSv_2.Complexity = 'real';
crt_PT_8c0022_GPS_nSv_2.SampleTime = -1;
crt_PT_8c0022_GPS_nSv_2.SamplingMode = 'Sample based';
crt_PT_8c0022_GPS_nSv_2.InitialValue = '';
% Signal crt_PT_8c0022_GPS_nSv_RTK
crt_PT_8c0022_GPS_nSv_RTK = Simulink.Signal;
crt_PT_8c0022_GPS_nSv_RTK.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0022_GPS_nSv_RTK.RTWInfo.Alias = '';
crt_PT_8c0022_GPS_nSv_RTK.Description = ...
  ['Number of common satellites available to RTK solution' char(10) ...
   'Frame: RT_SB_GPS_Status, 9175074 (0x8c0022).' char(10) ...
   'Signal: GPS_nSv_RTK.' char(10) ...
   'Range (world values): 0.0 ... 16.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0022_GPS_nSv_RTK.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0022_GPS_nSv_RTK.Min = 0.0;
crt_PT_8c0022_GPS_nSv_RTK.Max = 16.0;
crt_PT_8c0022_GPS_nSv_RTK.DocUnits = '';
crt_PT_8c0022_GPS_nSv_RTK.Dimensions = 1;
crt_PT_8c0022_GPS_nSv_RTK.Complexity = 'real';
crt_PT_8c0022_GPS_nSv_RTK.SampleTime = -1;
crt_PT_8c0022_GPS_nSv_RTK.SamplingMode = 'Sample based';
crt_PT_8c0022_GPS_nSv_RTK.InitialValue = '';
% Signal crt_PT_8c0022_RTK_Status
crt_PT_8c0022_RTK_Status = Simulink.Signal;
crt_PT_8c0022_RTK_Status.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0022_RTK_Status.RTWInfo.Alias = '';
crt_PT_8c0022_RTK_Status.Description = ...
  ['Frame: RT_SB_GPS_Status, 9175074 (0x8c0022).' char(10) ...
   'Signal: RTK_Status.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0022_RTK_Status.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0022_RTK_Status.Min = 0.0;
crt_PT_8c0022_RTK_Status.Max = 255.0;
crt_PT_8c0022_RTK_Status.DocUnits = '';
crt_PT_8c0022_RTK_Status.Dimensions = 1;
crt_PT_8c0022_RTK_Status.Complexity = 'real';
crt_PT_8c0022_RTK_Status.SampleTime = -1;
crt_PT_8c0022_RTK_Status.SamplingMode = 'Sample based';
crt_PT_8c0022_RTK_Status.InitialValue = '';

% Frame RT_SB_GPS_Pos_ECEF_2, 9176354 (0x8c0522)
% Signal crt_PT_8c0522_GPS_Pos_ECEF_Y
crt_PT_8c0522_GPS_Pos_ECEF_Y = Simulink.Signal;
crt_PT_8c0522_GPS_Pos_ECEF_Y.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0522_GPS_Pos_ECEF_Y.RTWInfo.Alias = '';
crt_PT_8c0522_GPS_Pos_ECEF_Y.Description = ...
  ['ECEF Y position.  The ECEF Y axis originates from the Earth centre, and the positive Y axis intersects the Earth surface at zero degrees latittude and 90 degrees longitude.' char(10) ...
   'Frame: RT_SB_GPS_Pos_ECEF_2, 9176354 (0x8c0522).' char(10) ...
   'Signal: GPS_Pos_ECEF_Y.' char(10) ...
   'Range (world values): -1.0E7 ... 1.0E7 [m].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8c0522_GPS_Pos_ECEF_Y.DataType = 'fixdt(1, 32, 0.01, 0.0)';
crt_PT_8c0522_GPS_Pos_ECEF_Y.Min = -1.0E7;
crt_PT_8c0522_GPS_Pos_ECEF_Y.Max = 1.0E7;
crt_PT_8c0522_GPS_Pos_ECEF_Y.DocUnits = 'm';
crt_PT_8c0522_GPS_Pos_ECEF_Y.Dimensions = 1;
crt_PT_8c0522_GPS_Pos_ECEF_Y.Complexity = 'real';
crt_PT_8c0522_GPS_Pos_ECEF_Y.SampleTime = -1;
crt_PT_8c0522_GPS_Pos_ECEF_Y.SamplingMode = 'Sample based';
crt_PT_8c0522_GPS_Pos_ECEF_Y.InitialValue = '';
% Signal crt_PT_8c0522_GPS_Pos_ECEF_Z
crt_PT_8c0522_GPS_Pos_ECEF_Z = Simulink.Signal;
crt_PT_8c0522_GPS_Pos_ECEF_Z.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0522_GPS_Pos_ECEF_Z.RTWInfo.Alias = '';
crt_PT_8c0522_GPS_Pos_ECEF_Z.Description = ...
  ['ECEF Z position.  The ECEF Z axis originates from the Earth centre, and the positive Z axis intersects the Earth surface at the North Pole.' char(10) ...
   'Frame: RT_SB_GPS_Pos_ECEF_2, 9176354 (0x8c0522).' char(10) ...
   'Signal: GPS_Pos_ECEF_Z.' char(10) ...
   'Range (world values): -1.0E7 ... 1.0E7 [m].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8c0522_GPS_Pos_ECEF_Z.DataType = 'fixdt(1, 32, 0.01, 0.0)';
crt_PT_8c0522_GPS_Pos_ECEF_Z.Min = -1.0E7;
crt_PT_8c0522_GPS_Pos_ECEF_Z.Max = 1.0E7;
crt_PT_8c0522_GPS_Pos_ECEF_Z.DocUnits = 'm';
crt_PT_8c0522_GPS_Pos_ECEF_Z.Dimensions = 1;
crt_PT_8c0522_GPS_Pos_ECEF_Z.Complexity = 'real';
crt_PT_8c0522_GPS_Pos_ECEF_Z.SampleTime = -1;
crt_PT_8c0522_GPS_Pos_ECEF_Z.SamplingMode = 'Sample based';
crt_PT_8c0522_GPS_Pos_ECEF_Z.InitialValue = '';

% Frame RT_SB_GPS_Pos_ECEF_1, 9176098 (0x8c0422)
% Signal crt_PT_8c0422_Validity_GPS_Pos_ECEF_X
crt_PT_8c0422_Validity_GPS_Pos_ECEF_X = Simulink.Signal;
crt_PT_8c0422_Validity_GPS_Pos_ECEF_X.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_X.RTWInfo.Alias = '';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_X.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Pos_ECEF_1, 9176098 (0x8c0422).' char(10) ...
   'Signal: Validity_GPS_Pos_ECEF_X.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0422_Validity_GPS_Pos_ECEF_X.DataType = 'boolean';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_X.Min = 0.0;
crt_PT_8c0422_Validity_GPS_Pos_ECEF_X.Max = 1.0;
crt_PT_8c0422_Validity_GPS_Pos_ECEF_X.DocUnits = '';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_X.Dimensions = 1;
crt_PT_8c0422_Validity_GPS_Pos_ECEF_X.Complexity = 'real';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_X.SampleTime = -1;
crt_PT_8c0422_Validity_GPS_Pos_ECEF_X.SamplingMode = 'Sample based';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_X.InitialValue = '';
% Signal crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y = Simulink.Signal;
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y.RTWInfo.Alias = '';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Pos_ECEF_1, 9176098 (0x8c0422).' char(10) ...
   'Signal: Validity_GPS_Pos_ECEF_Y.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y.DataType = 'boolean';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y.Min = 0.0;
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y.Max = 1.0;
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y.DocUnits = '';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y.Dimensions = 1;
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y.Complexity = 'real';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y.SampleTime = -1;
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y.SamplingMode = 'Sample based';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Y.InitialValue = '';
% Signal crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z = Simulink.Signal;
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z.RTWInfo.Alias = '';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Pos_ECEF_1, 9176098 (0x8c0422).' char(10) ...
   'Signal: Validity_GPS_Pos_ECEF_Z.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z.DataType = 'boolean';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z.Min = 0.0;
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z.Max = 1.0;
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z.DocUnits = '';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z.Dimensions = 1;
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z.Complexity = 'real';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z.SampleTime = -1;
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z.SamplingMode = 'Sample based';
crt_PT_8c0422_Validity_GPS_Pos_ECEF_Z.InitialValue = '';
% Signal crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X = Simulink.Signal;
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X.RTWInfo.Alias = '';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_GPS_Pos_ECEF_1, 9176098 (0x8c0422).' char(10) ...
   'Signal: Accuracy_GPS_Pos_ECEF_X.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X.Min = 0.0;
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X.Max = 255.0;
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X.DocUnits = '';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X.Dimensions = 1;
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X.Complexity = 'real';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X.SampleTime = -1;
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X.SamplingMode = 'Sample based';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_X.InitialValue = '';
% Signal crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y = Simulink.Signal;
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y.RTWInfo.Alias = '';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_GPS_Pos_ECEF_1, 9176098 (0x8c0422).' char(10) ...
   'Signal: Accuracy_GPS_Pos_ECEF_Y.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y.Min = 0.0;
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y.Max = 255.0;
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y.DocUnits = '';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y.Dimensions = 1;
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y.Complexity = 'real';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y.SampleTime = -1;
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y.SamplingMode = 'Sample based';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Y.InitialValue = '';
% Signal crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z = Simulink.Signal;
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z.RTWInfo.Alias = '';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_GPS_Pos_ECEF_1, 9176098 (0x8c0422).' char(10) ...
   'Signal: Accuracy_GPS_Pos_ECEF_Z.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z.Min = 0.0;
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z.Max = 255.0;
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z.DocUnits = '';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z.Dimensions = 1;
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z.Complexity = 'real';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z.SampleTime = -1;
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z.SamplingMode = 'Sample based';
crt_PT_8c0422_Accuracy_GPS_Pos_ECEF_Z.InitialValue = '';
% Signal crt_PT_8c0422_GPS_Pos_ECEF_X
crt_PT_8c0422_GPS_Pos_ECEF_X = Simulink.Signal;
crt_PT_8c0422_GPS_Pos_ECEF_X.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0422_GPS_Pos_ECEF_X.RTWInfo.Alias = '';
crt_PT_8c0422_GPS_Pos_ECEF_X.Description = ...
  ['ECEF X position.  The ECEF X axis originates from the Earth centre, and the positive X axis intersects the Earth surface at zero degrees latittude and zero degrees longitude (the intersection of the equator and the prime meridian).' char(10) ...
   'Frame: RT_SB_GPS_Pos_ECEF_1, 9176098 (0x8c0422).' char(10) ...
   'Signal: GPS_Pos_ECEF_X.' char(10) ...
   'Range (world values): -1.0E7 ... 1.0E7 [m].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8c0422_GPS_Pos_ECEF_X.DataType = 'fixdt(1, 32, 0.01, 0.0)';
crt_PT_8c0422_GPS_Pos_ECEF_X.Min = -1.0E7;
crt_PT_8c0422_GPS_Pos_ECEF_X.Max = 1.0E7;
crt_PT_8c0422_GPS_Pos_ECEF_X.DocUnits = 'm';
crt_PT_8c0422_GPS_Pos_ECEF_X.Dimensions = 1;
crt_PT_8c0422_GPS_Pos_ECEF_X.Complexity = 'real';
crt_PT_8c0422_GPS_Pos_ECEF_X.SampleTime = -1;
crt_PT_8c0422_GPS_Pos_ECEF_X.SamplingMode = 'Sample based';
crt_PT_8c0422_GPS_Pos_ECEF_X.InitialValue = '';

% Frame RT_SB_GPS_Pos_LLH_2, 9175842 (0x8c0322)
% Signal crt_PT_8c0322_GPS_Pos_LLH_Longitude
crt_PT_8c0322_GPS_Pos_LLH_Longitude = Simulink.Signal;
crt_PT_8c0322_GPS_Pos_LLH_Longitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0322_GPS_Pos_LLH_Longitude.RTWInfo.Alias = '';
crt_PT_8c0322_GPS_Pos_LLH_Longitude.Description = ...
  ['Frame: RT_SB_GPS_Pos_LLH_2, 9175842 (0x8c0322).' char(10) ...
   'Signal: GPS_Pos_LLH_Longitude.' char(10) ...
   'Range (world values): -180.0 ... 180.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 1.0E-7*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8c0322_GPS_Pos_LLH_Longitude.DataType = 'fixdt(1, 32, 1.0E-7, 0.0)';
crt_PT_8c0322_GPS_Pos_LLH_Longitude.Min = -180.0;
crt_PT_8c0322_GPS_Pos_LLH_Longitude.Max = 180.0;
crt_PT_8c0322_GPS_Pos_LLH_Longitude.DocUnits = 'degrees';
crt_PT_8c0322_GPS_Pos_LLH_Longitude.Dimensions = 1;
crt_PT_8c0322_GPS_Pos_LLH_Longitude.Complexity = 'real';
crt_PT_8c0322_GPS_Pos_LLH_Longitude.SampleTime = -1;
crt_PT_8c0322_GPS_Pos_LLH_Longitude.SamplingMode = 'Sample based';
crt_PT_8c0322_GPS_Pos_LLH_Longitude.InitialValue = '';
% Signal crt_PT_8c0322_GPS_Pos_LLH_Altitude
crt_PT_8c0322_GPS_Pos_LLH_Altitude = Simulink.Signal;
crt_PT_8c0322_GPS_Pos_LLH_Altitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0322_GPS_Pos_LLH_Altitude.RTWInfo.Alias = '';
crt_PT_8c0322_GPS_Pos_LLH_Altitude.Description = ...
  ['Frame: RT_SB_GPS_Pos_LLH_2, 9175842 (0x8c0322).' char(10) ...
   'Signal: GPS_Pos_LLH_Altitude.' char(10) ...
   'Range (world values): -1000.0 ... 100000.0 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8c0322_GPS_Pos_LLH_Altitude.DataType = 'fixdt(1, 32, 0.001, 0.0)';
crt_PT_8c0322_GPS_Pos_LLH_Altitude.Min = -1000.0;
crt_PT_8c0322_GPS_Pos_LLH_Altitude.Max = 100000.0;
crt_PT_8c0322_GPS_Pos_LLH_Altitude.DocUnits = 'm';
crt_PT_8c0322_GPS_Pos_LLH_Altitude.Dimensions = 1;
crt_PT_8c0322_GPS_Pos_LLH_Altitude.Complexity = 'real';
crt_PT_8c0322_GPS_Pos_LLH_Altitude.SampleTime = -1;
crt_PT_8c0322_GPS_Pos_LLH_Altitude.SamplingMode = 'Sample based';
crt_PT_8c0322_GPS_Pos_LLH_Altitude.InitialValue = '';

% Frame RT_SB_GPS_Pos_LLH_1, 9175586 (0x8c0222)
% Signal crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude
crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude = Simulink.Signal;
crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude.RTWInfo.Alias = '';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Pos_LLH_1, 9175586 (0x8c0222).' char(10) ...
   'Signal: Validity_GPS_Pos_LLH_Latitude.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude.DataType = 'boolean';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude.Min = 0.0;
crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude.Max = 1.0;
crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude.DocUnits = '';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude.Dimensions = 1;
crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude.Complexity = 'real';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude.SampleTime = -1;
crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude.SamplingMode = 'Sample based';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Latitude.InitialValue = '';
% Signal crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude
crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude = Simulink.Signal;
crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude.RTWInfo.Alias = '';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Pos_LLH_1, 9175586 (0x8c0222).' char(10) ...
   'Signal: Validity_GPS_Pos_LLH_Longitude.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude.DataType = 'boolean';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude.Min = 0.0;
crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude.Max = 1.0;
crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude.DocUnits = '';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude.Dimensions = 1;
crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude.Complexity = 'real';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude.SampleTime = -1;
crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude.SamplingMode = 'Sample based';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Longitude.InitialValue = '';
% Signal crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude
crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude = Simulink.Signal;
crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude.RTWInfo.Alias = '';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Pos_LLH_1, 9175586 (0x8c0222).' char(10) ...
   'Signal: Validity_GPS_Pos_LLH_Altitude.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude.DataType = 'boolean';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude.Min = 0.0;
crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude.Max = 1.0;
crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude.DocUnits = '';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude.Dimensions = 1;
crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude.Complexity = 'real';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude.SampleTime = -1;
crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude.SamplingMode = 'Sample based';
crt_PT_8c0222_Validity_GPS_Pos_LLH_Altitude.InitialValue = '';
% Signal crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude = Simulink.Signal;
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude.RTWInfo.Alias = '';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude.Description = ...
  ['This accuracy value applies to both 2D and 3D GPS speed.' char(10) ...
   'Frame: RT_SB_GPS_Pos_LLH_1, 9175586 (0x8c0222).' char(10) ...
   'Signal: Accuracy_GPS_Pos_LLH_Latitude.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude.Min = 0.0;
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude.Max = 255.0;
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude.DocUnits = '';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude.Dimensions = 1;
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude.Complexity = 'real';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude.SampleTime = -1;
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude.SamplingMode = 'Sample based';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Latitude.InitialValue = '';
% Signal crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude = Simulink.Signal;
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude.RTWInfo.Alias = '';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude.Description = ...
  ['This accuracy value applies to both 2D and 3D GPS speed.' char(10) ...
   'Frame: RT_SB_GPS_Pos_LLH_1, 9175586 (0x8c0222).' char(10) ...
   'Signal: Accuracy_GPS_Pos_LLH_Longitude.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude.Min = 0.0;
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude.Max = 255.0;
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude.DocUnits = '';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude.Dimensions = 1;
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude.Complexity = 'real';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude.SampleTime = -1;
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude.SamplingMode = 'Sample based';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Longitude.InitialValue = '';
% Signal crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude = Simulink.Signal;
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude.RTWInfo.Alias = '';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude.Description = ...
  ['This accuracy value applies to both 2D and 3D GPS speed.' char(10) ...
   'Frame: RT_SB_GPS_Pos_LLH_1, 9175586 (0x8c0222).' char(10) ...
   'Signal: Accuracy_GPS_Pos_LLH_Altitude.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude.Min = 0.0;
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude.Max = 255.0;
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude.DocUnits = '';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude.Dimensions = 1;
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude.Complexity = 'real';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude.SampleTime = -1;
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude.SamplingMode = 'Sample based';
crt_PT_8c0222_Accuracy_GPS_Pos_LLH_Altitude.InitialValue = '';
% Signal crt_PT_8c0222_GPS_Pos_LLH_Latitude
crt_PT_8c0222_GPS_Pos_LLH_Latitude = Simulink.Signal;
crt_PT_8c0222_GPS_Pos_LLH_Latitude.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c0222_GPS_Pos_LLH_Latitude.RTWInfo.Alias = '';
crt_PT_8c0222_GPS_Pos_LLH_Latitude.Description = ...
  ['Frame: RT_SB_GPS_Pos_LLH_1, 9175586 (0x8c0222).' char(10) ...
   'Signal: GPS_Pos_LLH_Latitude.' char(10) ...
   'Range (world values): -90.0 ... 90.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 1.0E-7*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8c0222_GPS_Pos_LLH_Latitude.DataType = 'fixdt(1, 32, 1.0E-7, 0.0)';
crt_PT_8c0222_GPS_Pos_LLH_Latitude.Min = -90.0;
crt_PT_8c0222_GPS_Pos_LLH_Latitude.Max = 90.0;
crt_PT_8c0222_GPS_Pos_LLH_Latitude.DocUnits = 'degrees';
crt_PT_8c0222_GPS_Pos_LLH_Latitude.Dimensions = 1;
crt_PT_8c0222_GPS_Pos_LLH_Latitude.Complexity = 'real';
crt_PT_8c0222_GPS_Pos_LLH_Latitude.SampleTime = -1;
crt_PT_8c0222_GPS_Pos_LLH_Latitude.SamplingMode = 'Sample based';
crt_PT_8c0222_GPS_Pos_LLH_Latitude.InitialValue = '';

% Frame RT_SB_GPS_Heading_Gradient, 9180450 (0x8c1522)
% Signal crt_PT_8c1522_Validity_GPS_Heading
crt_PT_8c1522_Validity_GPS_Heading = Simulink.Signal;
crt_PT_8c1522_Validity_GPS_Heading.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1522_Validity_GPS_Heading.RTWInfo.Alias = '';
crt_PT_8c1522_Validity_GPS_Heading.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Heading_Gradient, 9180450 (0x8c1522).' char(10) ...
   'Signal: Validity_GPS_Heading.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c1522_Validity_GPS_Heading.DataType = 'boolean';
crt_PT_8c1522_Validity_GPS_Heading.Min = 0.0;
crt_PT_8c1522_Validity_GPS_Heading.Max = 1.0;
crt_PT_8c1522_Validity_GPS_Heading.DocUnits = '';
crt_PT_8c1522_Validity_GPS_Heading.Dimensions = 1;
crt_PT_8c1522_Validity_GPS_Heading.Complexity = 'real';
crt_PT_8c1522_Validity_GPS_Heading.SampleTime = -1;
crt_PT_8c1522_Validity_GPS_Heading.SamplingMode = 'Sample based';
crt_PT_8c1522_Validity_GPS_Heading.InitialValue = '';
% Signal crt_PT_8c1522_Validity_GPS_Gradient
crt_PT_8c1522_Validity_GPS_Gradient = Simulink.Signal;
crt_PT_8c1522_Validity_GPS_Gradient.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1522_Validity_GPS_Gradient.RTWInfo.Alias = '';
crt_PT_8c1522_Validity_GPS_Gradient.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Heading_Gradient, 9180450 (0x8c1522).' char(10) ...
   'Signal: Validity_GPS_Gradient.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c1522_Validity_GPS_Gradient.DataType = 'boolean';
crt_PT_8c1522_Validity_GPS_Gradient.Min = 0.0;
crt_PT_8c1522_Validity_GPS_Gradient.Max = 1.0;
crt_PT_8c1522_Validity_GPS_Gradient.DocUnits = '';
crt_PT_8c1522_Validity_GPS_Gradient.Dimensions = 1;
crt_PT_8c1522_Validity_GPS_Gradient.Complexity = 'real';
crt_PT_8c1522_Validity_GPS_Gradient.SampleTime = -1;
crt_PT_8c1522_Validity_GPS_Gradient.SamplingMode = 'Sample based';
crt_PT_8c1522_Validity_GPS_Gradient.InitialValue = '';
% Signal crt_PT_8c1522_Accuracy_GPS_Heading
crt_PT_8c1522_Accuracy_GPS_Heading = Simulink.Signal;
crt_PT_8c1522_Accuracy_GPS_Heading.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1522_Accuracy_GPS_Heading.RTWInfo.Alias = '';
crt_PT_8c1522_Accuracy_GPS_Heading.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_GPS_Heading_Gradient, 9180450 (0x8c1522).' char(10) ...
   'Signal: Accuracy_GPS_Heading.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c1522_Accuracy_GPS_Heading.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c1522_Accuracy_GPS_Heading.Min = 0.0;
crt_PT_8c1522_Accuracy_GPS_Heading.Max = 255.0;
crt_PT_8c1522_Accuracy_GPS_Heading.DocUnits = '';
crt_PT_8c1522_Accuracy_GPS_Heading.Dimensions = 1;
crt_PT_8c1522_Accuracy_GPS_Heading.Complexity = 'real';
crt_PT_8c1522_Accuracy_GPS_Heading.SampleTime = -1;
crt_PT_8c1522_Accuracy_GPS_Heading.SamplingMode = 'Sample based';
crt_PT_8c1522_Accuracy_GPS_Heading.InitialValue = '';
% Signal crt_PT_8c1522_GPS_Heading
crt_PT_8c1522_GPS_Heading = Simulink.Signal;
crt_PT_8c1522_GPS_Heading.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1522_GPS_Heading.RTWInfo.Alias = '';
crt_PT_8c1522_GPS_Heading.Description = ...
  ['This is GPS heading, the direction that the vehicle is travelling in the local horizontal plane.' char(10) ...
   'Frame: RT_SB_GPS_Heading_Gradient, 9180450 (0x8c1522).' char(10) ...
   'Signal: GPS_Heading.' char(10) ...
   'Range (world values): -180.0 ... 180.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8c1522_GPS_Heading.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8c1522_GPS_Heading.Min = -180.0;
crt_PT_8c1522_GPS_Heading.Max = 180.0;
crt_PT_8c1522_GPS_Heading.DocUnits = 'degrees';
crt_PT_8c1522_GPS_Heading.Dimensions = 1;
crt_PT_8c1522_GPS_Heading.Complexity = 'real';
crt_PT_8c1522_GPS_Heading.SampleTime = -1;
crt_PT_8c1522_GPS_Heading.SamplingMode = 'Sample based';
crt_PT_8c1522_GPS_Heading.InitialValue = '';
% Signal crt_PT_8c1522_Accuracy_GPS_Gradient
crt_PT_8c1522_Accuracy_GPS_Gradient = Simulink.Signal;
crt_PT_8c1522_Accuracy_GPS_Gradient.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1522_Accuracy_GPS_Gradient.RTWInfo.Alias = '';
crt_PT_8c1522_Accuracy_GPS_Gradient.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_GPS_Heading_Gradient, 9180450 (0x8c1522).' char(10) ...
   'Signal: Accuracy_GPS_Gradient.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c1522_Accuracy_GPS_Gradient.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c1522_Accuracy_GPS_Gradient.Min = 0.0;
crt_PT_8c1522_Accuracy_GPS_Gradient.Max = 255.0;
crt_PT_8c1522_Accuracy_GPS_Gradient.DocUnits = '';
crt_PT_8c1522_Accuracy_GPS_Gradient.Dimensions = 1;
crt_PT_8c1522_Accuracy_GPS_Gradient.Complexity = 'real';
crt_PT_8c1522_Accuracy_GPS_Gradient.SampleTime = -1;
crt_PT_8c1522_Accuracy_GPS_Gradient.SamplingMode = 'Sample based';
crt_PT_8c1522_Accuracy_GPS_Gradient.InitialValue = '';
% Signal crt_PT_8c1522_GPS_Gradient
crt_PT_8c1522_GPS_Gradient = Simulink.Signal;
crt_PT_8c1522_GPS_Gradient.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1522_GPS_Gradient.RTWInfo.Alias = '';
crt_PT_8c1522_GPS_Gradient.Description = ...
  ['This is GPS gradient, i.e. the vertical direction that the vehicle is travelling, NOT pointing (pitch).' char(10) ...
   'Frame: RT_SB_GPS_Heading_Gradient, 9180450 (0x8c1522).' char(10) ...
   'Signal: GPS_Gradient.' char(10) ...
   'Range (world values): -90.0 ... 90.0 [degrees].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees]' ...
  ];
crt_PT_8c1522_GPS_Gradient.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_8c1522_GPS_Gradient.Min = -90.0;
crt_PT_8c1522_GPS_Gradient.Max = 90.0;
crt_PT_8c1522_GPS_Gradient.DocUnits = 'degrees';
crt_PT_8c1522_GPS_Gradient.Dimensions = 1;
crt_PT_8c1522_GPS_Gradient.Complexity = 'real';
crt_PT_8c1522_GPS_Gradient.SampleTime = -1;
crt_PT_8c1522_GPS_Gradient.SamplingMode = 'Sample based';
crt_PT_8c1522_GPS_Gradient.InitialValue = '';

% Frame RT_SB_GPS_Vel_ECEF_2, 9180194 (0x8c1422)
% Signal crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y = Simulink.Signal;
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y.RTWInfo.Alias = '';
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Vel_ECEF_2, 9180194 (0x8c1422).' char(10) ...
   'Signal: Validity_GPS_Vel_ECEF_Y.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y.DataType = 'boolean';
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y.Min = 0.0;
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y.Max = 1.0;
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y.DocUnits = '';
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y.Dimensions = 1;
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y.Complexity = 'real';
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y.SampleTime = -1;
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y.SamplingMode = 'Sample based';
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Y.InitialValue = '';
% Signal crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z = Simulink.Signal;
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z.RTWInfo.Alias = '';
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Vel_ECEF_2, 9180194 (0x8c1422).' char(10) ...
   'Signal: Validity_GPS_Vel_ECEF_Z.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z.DataType = 'boolean';
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z.Min = 0.0;
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z.Max = 1.0;
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z.DocUnits = '';
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z.Dimensions = 1;
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z.Complexity = 'real';
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z.SampleTime = -1;
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z.SamplingMode = 'Sample based';
crt_PT_8c1422_Validity_GPS_Vel_ECEF_Z.InitialValue = '';
% Signal crt_PT_8c1422_GPS_Vel_ECEF_Y
crt_PT_8c1422_GPS_Vel_ECEF_Y = Simulink.Signal;
crt_PT_8c1422_GPS_Vel_ECEF_Y.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1422_GPS_Vel_ECEF_Y.RTWInfo.Alias = '';
crt_PT_8c1422_GPS_Vel_ECEF_Y.Description = ...
  ['ECEF Y velocity.  The ECEF Y axis originates from the Earth centre, and the positive Y axis intersects the Earth surface at zero degrees latittude and 90 degrees longitude.' char(10) ...
   'Frame: RT_SB_GPS_Vel_ECEF_2, 9180194 (0x8c1422).' char(10) ...
   'Signal: GPS_Vel_ECEF_Y.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8c1422_GPS_Vel_ECEF_Y.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8c1422_GPS_Vel_ECEF_Y.Min = -838.0;
crt_PT_8c1422_GPS_Vel_ECEF_Y.Max = 838.0;
crt_PT_8c1422_GPS_Vel_ECEF_Y.DocUnits = 'm/s';
crt_PT_8c1422_GPS_Vel_ECEF_Y.Dimensions = 1;
crt_PT_8c1422_GPS_Vel_ECEF_Y.Complexity = 'real';
crt_PT_8c1422_GPS_Vel_ECEF_Y.SampleTime = -1;
crt_PT_8c1422_GPS_Vel_ECEF_Y.SamplingMode = 'Sample based';
crt_PT_8c1422_GPS_Vel_ECEF_Y.InitialValue = '';
% Signal crt_PT_8c1422_GPS_Vel_ECEF_Z
crt_PT_8c1422_GPS_Vel_ECEF_Z = Simulink.Signal;
crt_PT_8c1422_GPS_Vel_ECEF_Z.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1422_GPS_Vel_ECEF_Z.RTWInfo.Alias = '';
crt_PT_8c1422_GPS_Vel_ECEF_Z.Description = ...
  ['ECEF Z velocity.  The ECEF Z axis originates from the Earth centre, and the positive Z axis intersects the Earth surface at the North Pole.' char(10) ...
   'Frame: RT_SB_GPS_Vel_ECEF_2, 9180194 (0x8c1422).' char(10) ...
   'Signal: GPS_Vel_ECEF_Z.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8c1422_GPS_Vel_ECEF_Z.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8c1422_GPS_Vel_ECEF_Z.Min = -838.0;
crt_PT_8c1422_GPS_Vel_ECEF_Z.Max = 838.0;
crt_PT_8c1422_GPS_Vel_ECEF_Z.DocUnits = 'm/s';
crt_PT_8c1422_GPS_Vel_ECEF_Z.Dimensions = 1;
crt_PT_8c1422_GPS_Vel_ECEF_Z.Complexity = 'real';
crt_PT_8c1422_GPS_Vel_ECEF_Z.SampleTime = -1;
crt_PT_8c1422_GPS_Vel_ECEF_Z.SamplingMode = 'Sample based';
crt_PT_8c1422_GPS_Vel_ECEF_Z.InitialValue = '';

% Frame RT_SB_GPS_Vel_ECEF_1, 9179938 (0x8c1322)
% Signal crt_PT_8c1322_Validity_GPS_Vel_ECEF_X
crt_PT_8c1322_Validity_GPS_Vel_ECEF_X = Simulink.Signal;
crt_PT_8c1322_Validity_GPS_Vel_ECEF_X.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1322_Validity_GPS_Vel_ECEF_X.RTWInfo.Alias = '';
crt_PT_8c1322_Validity_GPS_Vel_ECEF_X.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Vel_ECEF_1, 9179938 (0x8c1322).' char(10) ...
   'Signal: Validity_GPS_Vel_ECEF_X.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c1322_Validity_GPS_Vel_ECEF_X.DataType = 'boolean';
crt_PT_8c1322_Validity_GPS_Vel_ECEF_X.Min = 0.0;
crt_PT_8c1322_Validity_GPS_Vel_ECEF_X.Max = 1.0;
crt_PT_8c1322_Validity_GPS_Vel_ECEF_X.DocUnits = '';
crt_PT_8c1322_Validity_GPS_Vel_ECEF_X.Dimensions = 1;
crt_PT_8c1322_Validity_GPS_Vel_ECEF_X.Complexity = 'real';
crt_PT_8c1322_Validity_GPS_Vel_ECEF_X.SampleTime = -1;
crt_PT_8c1322_Validity_GPS_Vel_ECEF_X.SamplingMode = 'Sample based';
crt_PT_8c1322_Validity_GPS_Vel_ECEF_X.InitialValue = '';
% Signal crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X = Simulink.Signal;
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X.RTWInfo.Alias = '';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X.Description = ...
  ['Frame: RT_SB_GPS_Vel_ECEF_1, 9179938 (0x8c1322).' char(10) ...
   'Signal: Accuracy_GPS_Vel_ECEF_X.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X.Min = 0.0;
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X.Max = 255.0;
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X.DocUnits = '';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X.Dimensions = 1;
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X.Complexity = 'real';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X.SampleTime = -1;
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X.SamplingMode = 'Sample based';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_X.InitialValue = '';
% Signal crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y = Simulink.Signal;
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y.RTWInfo.Alias = '';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y.Description = ...
  ['Frame: RT_SB_GPS_Vel_ECEF_1, 9179938 (0x8c1322).' char(10) ...
   'Signal: Accuracy_GPS_Vel_ECEF_Y.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y.Min = 0.0;
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y.Max = 255.0;
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y.DocUnits = '';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y.Dimensions = 1;
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y.Complexity = 'real';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y.SampleTime = -1;
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y.SamplingMode = 'Sample based';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Y.InitialValue = '';
% Signal crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z = Simulink.Signal;
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z.RTWInfo.Alias = '';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z.Description = ...
  ['Frame: RT_SB_GPS_Vel_ECEF_1, 9179938 (0x8c1322).' char(10) ...
   'Signal: Accuracy_GPS_Vel_ECEF_Z.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z.Min = 0.0;
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z.Max = 255.0;
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z.DocUnits = '';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z.Dimensions = 1;
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z.Complexity = 'real';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z.SampleTime = -1;
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z.SamplingMode = 'Sample based';
crt_PT_8c1322_Accuracy_GPS_Vel_ECEF_Z.InitialValue = '';
% Signal crt_PT_8c1322_GPS_Vel_ECEF_X
crt_PT_8c1322_GPS_Vel_ECEF_X = Simulink.Signal;
crt_PT_8c1322_GPS_Vel_ECEF_X.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8c1322_GPS_Vel_ECEF_X.RTWInfo.Alias = '';
crt_PT_8c1322_GPS_Vel_ECEF_X.Description = ...
  ['ECEF X velocity.  The ECEF X axis originates from the Earth centre, and the positive X axis intersects the Earth surface at zero degrees latittude and zero degrees longitude (the intersection of the equator and the prime meridian).' char(10) ...
   'Frame: RT_SB_GPS_Vel_ECEF_1, 9179938 (0x8c1322).' char(10) ...
   'Signal: GPS_Vel_ECEF_X.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_8c1322_GPS_Vel_ECEF_X.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_8c1322_GPS_Vel_ECEF_X.Min = -838.0;
crt_PT_8c1322_GPS_Vel_ECEF_X.Max = 838.0;
crt_PT_8c1322_GPS_Vel_ECEF_X.DocUnits = 'm/s';
crt_PT_8c1322_GPS_Vel_ECEF_X.Dimensions = 1;
crt_PT_8c1322_GPS_Vel_ECEF_X.Complexity = 'real';
crt_PT_8c1322_GPS_Vel_ECEF_X.SampleTime = -1;
crt_PT_8c1322_GPS_Vel_ECEF_X.SamplingMode = 'Sample based';
crt_PT_8c1322_GPS_Vel_ECEF_X.InitialValue = '';

% Frame RT_SB_GPS_Vel_NED_2, 0 (0x000)
% Signal crt_PT_000_Validity_GPS_Vel_NED_D
crt_PT_000_Validity_GPS_Vel_NED_D = Simulink.Signal;
crt_PT_000_Validity_GPS_Vel_NED_D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_000_Validity_GPS_Vel_NED_D.RTWInfo.Alias = '';
crt_PT_000_Validity_GPS_Vel_NED_D.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Vel_NED_2, 0 (0x000).' char(10) ...
   'Signal: Validity_GPS_Vel_NED_D.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_000_Validity_GPS_Vel_NED_D.DataType = 'boolean';
crt_PT_000_Validity_GPS_Vel_NED_D.Min = 0.0;
crt_PT_000_Validity_GPS_Vel_NED_D.Max = 1.0;
crt_PT_000_Validity_GPS_Vel_NED_D.DocUnits = '';
crt_PT_000_Validity_GPS_Vel_NED_D.Dimensions = 1;
crt_PT_000_Validity_GPS_Vel_NED_D.Complexity = 'real';
crt_PT_000_Validity_GPS_Vel_NED_D.SampleTime = -1;
crt_PT_000_Validity_GPS_Vel_NED_D.SamplingMode = 'Sample based';
crt_PT_000_Validity_GPS_Vel_NED_D.InitialValue = '';
% Signal crt_PT_000_Accuracy_GPS_Vel_D
crt_PT_000_Accuracy_GPS_Vel_D = Simulink.Signal;
crt_PT_000_Accuracy_GPS_Vel_D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_000_Accuracy_GPS_Vel_D.RTWInfo.Alias = '';
crt_PT_000_Accuracy_GPS_Vel_D.Description = ...
  ['Frame: RT_SB_GPS_Vel_NED_2, 0 (0x000).' char(10) ...
   'Signal: Accuracy_GPS_Vel_D.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_000_Accuracy_GPS_Vel_D.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_000_Accuracy_GPS_Vel_D.Min = 0.0;
crt_PT_000_Accuracy_GPS_Vel_D.Max = 255.0;
crt_PT_000_Accuracy_GPS_Vel_D.DocUnits = '';
crt_PT_000_Accuracy_GPS_Vel_D.Dimensions = 1;
crt_PT_000_Accuracy_GPS_Vel_D.Complexity = 'real';
crt_PT_000_Accuracy_GPS_Vel_D.SampleTime = -1;
crt_PT_000_Accuracy_GPS_Vel_D.SamplingMode = 'Sample based';
crt_PT_000_Accuracy_GPS_Vel_D.InitialValue = '';
% Signal crt_PT_000_GPS_Vel_NED_D
crt_PT_000_GPS_Vel_NED_D = Simulink.Signal;
crt_PT_000_GPS_Vel_NED_D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_000_GPS_Vel_NED_D.RTWInfo.Alias = '';
crt_PT_000_GPS_Vel_NED_D.Description = ...
  ['VELNED D velocity.  This is the velocity vector directly downwards towards the Earth centre at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_GPS_Vel_NED_2, 0 (0x000).' char(10) ...
   'Signal: GPS_Vel_NED_D.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_000_GPS_Vel_NED_D.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_000_GPS_Vel_NED_D.Min = -838.0;
crt_PT_000_GPS_Vel_NED_D.Max = 838.0;
crt_PT_000_GPS_Vel_NED_D.DocUnits = 'm/s';
crt_PT_000_GPS_Vel_NED_D.Dimensions = 1;
crt_PT_000_GPS_Vel_NED_D.Complexity = 'real';
crt_PT_000_GPS_Vel_NED_D.SampleTime = -1;
crt_PT_000_GPS_Vel_NED_D.SamplingMode = 'Sample based';
crt_PT_000_GPS_Vel_NED_D.InitialValue = '';

% Frame RT_SB_GPS_Vel_NED_1, 536870911 (0x1fffffff)
% Signal crt_PT_1fffffff_Validity_GPS_Vel_NED_N
crt_PT_1fffffff_Validity_GPS_Vel_NED_N = Simulink.Signal;
crt_PT_1fffffff_Validity_GPS_Vel_NED_N.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_1fffffff_Validity_GPS_Vel_NED_N.RTWInfo.Alias = '';
crt_PT_1fffffff_Validity_GPS_Vel_NED_N.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Vel_NED_1, 536870911 (0x1fffffff).' char(10) ...
   'Signal: Validity_GPS_Vel_NED_N.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_1fffffff_Validity_GPS_Vel_NED_N.DataType = 'boolean';
crt_PT_1fffffff_Validity_GPS_Vel_NED_N.Min = 0.0;
crt_PT_1fffffff_Validity_GPS_Vel_NED_N.Max = 1.0;
crt_PT_1fffffff_Validity_GPS_Vel_NED_N.DocUnits = '';
crt_PT_1fffffff_Validity_GPS_Vel_NED_N.Dimensions = 1;
crt_PT_1fffffff_Validity_GPS_Vel_NED_N.Complexity = 'real';
crt_PT_1fffffff_Validity_GPS_Vel_NED_N.SampleTime = -1;
crt_PT_1fffffff_Validity_GPS_Vel_NED_N.SamplingMode = 'Sample based';
crt_PT_1fffffff_Validity_GPS_Vel_NED_N.InitialValue = '';
% Signal crt_PT_1fffffff_Validity_GPS_Vel_NED_E
crt_PT_1fffffff_Validity_GPS_Vel_NED_E = Simulink.Signal;
crt_PT_1fffffff_Validity_GPS_Vel_NED_E.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_1fffffff_Validity_GPS_Vel_NED_E.RTWInfo.Alias = '';
crt_PT_1fffffff_Validity_GPS_Vel_NED_E.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Vel_NED_1, 536870911 (0x1fffffff).' char(10) ...
   'Signal: Validity_GPS_Vel_NED_E.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_1fffffff_Validity_GPS_Vel_NED_E.DataType = 'boolean';
crt_PT_1fffffff_Validity_GPS_Vel_NED_E.Min = 0.0;
crt_PT_1fffffff_Validity_GPS_Vel_NED_E.Max = 1.0;
crt_PT_1fffffff_Validity_GPS_Vel_NED_E.DocUnits = '';
crt_PT_1fffffff_Validity_GPS_Vel_NED_E.Dimensions = 1;
crt_PT_1fffffff_Validity_GPS_Vel_NED_E.Complexity = 'real';
crt_PT_1fffffff_Validity_GPS_Vel_NED_E.SampleTime = -1;
crt_PT_1fffffff_Validity_GPS_Vel_NED_E.SamplingMode = 'Sample based';
crt_PT_1fffffff_Validity_GPS_Vel_NED_E.InitialValue = '';
% Signal crt_PT_1fffffff_Accuracy_GPS_Vel_NE
crt_PT_1fffffff_Accuracy_GPS_Vel_NE = Simulink.Signal;
crt_PT_1fffffff_Accuracy_GPS_Vel_NE.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_1fffffff_Accuracy_GPS_Vel_NE.RTWInfo.Alias = '';
crt_PT_1fffffff_Accuracy_GPS_Vel_NE.Description = ...
  ['Frame: RT_SB_GPS_Vel_NED_1, 536870911 (0x1fffffff).' char(10) ...
   'Signal: Accuracy_GPS_Vel_NE.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_1fffffff_Accuracy_GPS_Vel_NE.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_1fffffff_Accuracy_GPS_Vel_NE.Min = 0.0;
crt_PT_1fffffff_Accuracy_GPS_Vel_NE.Max = 255.0;
crt_PT_1fffffff_Accuracy_GPS_Vel_NE.DocUnits = '';
crt_PT_1fffffff_Accuracy_GPS_Vel_NE.Dimensions = 1;
crt_PT_1fffffff_Accuracy_GPS_Vel_NE.Complexity = 'real';
crt_PT_1fffffff_Accuracy_GPS_Vel_NE.SampleTime = -1;
crt_PT_1fffffff_Accuracy_GPS_Vel_NE.SamplingMode = 'Sample based';
crt_PT_1fffffff_Accuracy_GPS_Vel_NE.InitialValue = '';
% Signal crt_PT_1fffffff_GPS_Vel_NED_N
crt_PT_1fffffff_GPS_Vel_NED_N = Simulink.Signal;
crt_PT_1fffffff_GPS_Vel_NED_N.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_1fffffff_GPS_Vel_NED_N.RTWInfo.Alias = '';
crt_PT_1fffffff_GPS_Vel_NED_N.Description = ...
  ['VELNED N velocity.  This is the velocity vector directly North at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_GPS_Vel_NED_1, 536870911 (0x1fffffff).' char(10) ...
   'Signal: GPS_Vel_NED_N.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_1fffffff_GPS_Vel_NED_N.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_1fffffff_GPS_Vel_NED_N.Min = -838.0;
crt_PT_1fffffff_GPS_Vel_NED_N.Max = 838.0;
crt_PT_1fffffff_GPS_Vel_NED_N.DocUnits = 'm/s';
crt_PT_1fffffff_GPS_Vel_NED_N.Dimensions = 1;
crt_PT_1fffffff_GPS_Vel_NED_N.Complexity = 'real';
crt_PT_1fffffff_GPS_Vel_NED_N.SampleTime = -1;
crt_PT_1fffffff_GPS_Vel_NED_N.SamplingMode = 'Sample based';
crt_PT_1fffffff_GPS_Vel_NED_N.InitialValue = '';
% Signal crt_PT_1fffffff_GPS_Vel_NED_E
crt_PT_1fffffff_GPS_Vel_NED_E = Simulink.Signal;
crt_PT_1fffffff_GPS_Vel_NED_E.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_1fffffff_GPS_Vel_NED_E.RTWInfo.Alias = '';
crt_PT_1fffffff_GPS_Vel_NED_E.Description = ...
  ['VELNED E velocity.  This is the velocity vector directly East at the current local Earth surface position.' char(10) ...
   'Frame: RT_SB_GPS_Vel_NED_1, 536870911 (0x1fffffff).' char(10) ...
   'Signal: GPS_Vel_NED_E.' char(10) ...
   'Range (world values): -838.0 ... 838.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_1fffffff_GPS_Vel_NED_E.DataType = 'fixdt(1, 32, 1.0E-4, 0.0)';
crt_PT_1fffffff_GPS_Vel_NED_E.Min = -838.0;
crt_PT_1fffffff_GPS_Vel_NED_E.Max = 838.0;
crt_PT_1fffffff_GPS_Vel_NED_E.DocUnits = 'm/s';
crt_PT_1fffffff_GPS_Vel_NED_E.Dimensions = 1;
crt_PT_1fffffff_GPS_Vel_NED_E.Complexity = 'real';
crt_PT_1fffffff_GPS_Vel_NED_E.SampleTime = -1;
crt_PT_1fffffff_GPS_Vel_NED_E.SamplingMode = 'Sample based';
crt_PT_1fffffff_GPS_Vel_NED_E.InitialValue = '';

% Frame RT_SB_GPS_Speed, 1818 (0x71a)
% Signal crt_PT_71a_Validity_GPS_Speed_2D
crt_PT_71a_Validity_GPS_Speed_2D = Simulink.Signal;
crt_PT_71a_Validity_GPS_Speed_2D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_71a_Validity_GPS_Speed_2D.RTWInfo.Alias = '';
crt_PT_71a_Validity_GPS_Speed_2D.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Speed, 1818 (0x71a).' char(10) ...
   'Signal: Validity_GPS_Speed_2D.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_71a_Validity_GPS_Speed_2D.DataType = 'boolean';
crt_PT_71a_Validity_GPS_Speed_2D.Min = 0.0;
crt_PT_71a_Validity_GPS_Speed_2D.Max = 1.0;
crt_PT_71a_Validity_GPS_Speed_2D.DocUnits = '';
crt_PT_71a_Validity_GPS_Speed_2D.Dimensions = 1;
crt_PT_71a_Validity_GPS_Speed_2D.Complexity = 'real';
crt_PT_71a_Validity_GPS_Speed_2D.SampleTime = -1;
crt_PT_71a_Validity_GPS_Speed_2D.SamplingMode = 'Sample based';
crt_PT_71a_Validity_GPS_Speed_2D.InitialValue = '';
% Signal crt_PT_71a_Validity_GPS_Speed_3D
crt_PT_71a_Validity_GPS_Speed_3D = Simulink.Signal;
crt_PT_71a_Validity_GPS_Speed_3D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_71a_Validity_GPS_Speed_3D.RTWInfo.Alias = '';
crt_PT_71a_Validity_GPS_Speed_3D.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Speed, 1818 (0x71a).' char(10) ...
   'Signal: Validity_GPS_Speed_3D.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_71a_Validity_GPS_Speed_3D.DataType = 'boolean';
crt_PT_71a_Validity_GPS_Speed_3D.Min = 0.0;
crt_PT_71a_Validity_GPS_Speed_3D.Max = 1.0;
crt_PT_71a_Validity_GPS_Speed_3D.DocUnits = '';
crt_PT_71a_Validity_GPS_Speed_3D.Dimensions = 1;
crt_PT_71a_Validity_GPS_Speed_3D.Complexity = 'real';
crt_PT_71a_Validity_GPS_Speed_3D.SampleTime = -1;
crt_PT_71a_Validity_GPS_Speed_3D.SamplingMode = 'Sample based';
crt_PT_71a_Validity_GPS_Speed_3D.InitialValue = '';
% Signal crt_PT_71a_Accuracy_GPS_Speed
crt_PT_71a_Accuracy_GPS_Speed = Simulink.Signal;
crt_PT_71a_Accuracy_GPS_Speed.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_71a_Accuracy_GPS_Speed.RTWInfo.Alias = '';
crt_PT_71a_Accuracy_GPS_Speed.Description = ...
  ['This accuracy value applies to both 2D and 3D GPS speed.' char(10) ...
   'Frame: RT_SB_GPS_Speed, 1818 (0x71a).' char(10) ...
   'Signal: Accuracy_GPS_Speed.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_71a_Accuracy_GPS_Speed.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_71a_Accuracy_GPS_Speed.Min = 0.0;
crt_PT_71a_Accuracy_GPS_Speed.Max = 255.0;
crt_PT_71a_Accuracy_GPS_Speed.DocUnits = '';
crt_PT_71a_Accuracy_GPS_Speed.Dimensions = 1;
crt_PT_71a_Accuracy_GPS_Speed.Complexity = 'real';
crt_PT_71a_Accuracy_GPS_Speed.SampleTime = -1;
crt_PT_71a_Accuracy_GPS_Speed.SamplingMode = 'Sample based';
crt_PT_71a_Accuracy_GPS_Speed.InitialValue = '';
% Signal crt_PT_71a_GPS_Speed_2D
crt_PT_71a_GPS_Speed_2D = Simulink.Signal;
crt_PT_71a_GPS_Speed_2D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_71a_GPS_Speed_2D.RTWInfo.Alias = '';
crt_PT_71a_GPS_Speed_2D.Description = ...
  ['This is GPS scalar 2D speed - scalar speed with no local Z axis component included.' char(10) ...
   'Frame: RT_SB_GPS_Speed, 1818 (0x71a).' char(10) ...
   'Signal: GPS_Speed_2D.' char(10) ...
   'Range (world values): 0.0 ... 1675.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_71a_GPS_Speed_2D.DataType = 'fixdt(0, 32, 1.0E-4, 0.0)';
crt_PT_71a_GPS_Speed_2D.Min = 0.0;
crt_PT_71a_GPS_Speed_2D.Max = 1675.0;
crt_PT_71a_GPS_Speed_2D.DocUnits = 'm/s';
crt_PT_71a_GPS_Speed_2D.Dimensions = 1;
crt_PT_71a_GPS_Speed_2D.Complexity = 'real';
crt_PT_71a_GPS_Speed_2D.SampleTime = -1;
crt_PT_71a_GPS_Speed_2D.SamplingMode = 'Sample based';
crt_PT_71a_GPS_Speed_2D.InitialValue = '';
% Signal crt_PT_71a_GPS_Speed_3D
crt_PT_71a_GPS_Speed_3D = Simulink.Signal;
crt_PT_71a_GPS_Speed_3D.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_71a_GPS_Speed_3D.RTWInfo.Alias = '';
crt_PT_71a_GPS_Speed_3D.Description = ...
  ['This is GPS scalar 3D speed - scalar speed with the local Z axis component included.' char(10) ...
   'Frame: RT_SB_GPS_Speed, 1818 (0x71a).' char(10) ...
   'Signal: GPS_Speed_3D.' char(10) ...
   'Range (world values): 0.0 ... 1675.0 [m/s].' char(10) ...
   'Scaling: WorldValue = 1.0E-4*BinaryValue + 0.0 [m/s]' ...
  ];
crt_PT_71a_GPS_Speed_3D.DataType = 'fixdt(0, 32, 1.0E-4, 0.0)';
crt_PT_71a_GPS_Speed_3D.Min = 0.0;
crt_PT_71a_GPS_Speed_3D.Max = 1675.0;
crt_PT_71a_GPS_Speed_3D.DocUnits = 'm/s';
crt_PT_71a_GPS_Speed_3D.Dimensions = 1;
crt_PT_71a_GPS_Speed_3D.Complexity = 'real';
crt_PT_71a_GPS_Speed_3D.SampleTime = -1;
crt_PT_71a_GPS_Speed_3D.SamplingMode = 'Sample based';
crt_PT_71a_GPS_Speed_3D.InitialValue = '';

% Frame RT_SB_GPS_Time, 2047 (0x7ff)
% Signal crt_PT_7ff_Validity_GPS_Time
crt_PT_7ff_Validity_GPS_Time = Simulink.Signal;
crt_PT_7ff_Validity_GPS_Time.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_7ff_Validity_GPS_Time.RTWInfo.Alias = '';
crt_PT_7ff_Validity_GPS_Time.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Time, 2047 (0x7ff).' char(10) ...
   'Signal: Validity_GPS_Time.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_7ff_Validity_GPS_Time.DataType = 'boolean';
crt_PT_7ff_Validity_GPS_Time.Min = 0.0;
crt_PT_7ff_Validity_GPS_Time.Max = 1.0;
crt_PT_7ff_Validity_GPS_Time.DocUnits = '';
crt_PT_7ff_Validity_GPS_Time.Dimensions = 1;
crt_PT_7ff_Validity_GPS_Time.Complexity = 'real';
crt_PT_7ff_Validity_GPS_Time.SampleTime = -1;
crt_PT_7ff_Validity_GPS_Time.SamplingMode = 'Sample based';
crt_PT_7ff_Validity_GPS_Time.InitialValue = '';
% Signal crt_PT_7ff_Validity_GPS_Week
crt_PT_7ff_Validity_GPS_Week = Simulink.Signal;
crt_PT_7ff_Validity_GPS_Week.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_7ff_Validity_GPS_Week.RTWInfo.Alias = '';
crt_PT_7ff_Validity_GPS_Week.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_GPS_Time, 2047 (0x7ff).' char(10) ...
   'Signal: Validity_GPS_Week.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_7ff_Validity_GPS_Week.DataType = 'boolean';
crt_PT_7ff_Validity_GPS_Week.Min = 0.0;
crt_PT_7ff_Validity_GPS_Week.Max = 1.0;
crt_PT_7ff_Validity_GPS_Week.DocUnits = '';
crt_PT_7ff_Validity_GPS_Week.Dimensions = 1;
crt_PT_7ff_Validity_GPS_Week.Complexity = 'real';
crt_PT_7ff_Validity_GPS_Week.SampleTime = -1;
crt_PT_7ff_Validity_GPS_Week.SamplingMode = 'Sample based';
crt_PT_7ff_Validity_GPS_Week.InitialValue = '';
% Signal crt_PT_7ff_Accuracy_GPS_Time
crt_PT_7ff_Accuracy_GPS_Time = Simulink.Signal;
crt_PT_7ff_Accuracy_GPS_Time.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_7ff_Accuracy_GPS_Time.RTWInfo.Alias = '';
crt_PT_7ff_Accuracy_GPS_Time.Description = ...
  ['Frame: RT_SB_GPS_Time, 2047 (0x7ff).' char(10) ...
   'Signal: Accuracy_GPS_Time.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_7ff_Accuracy_GPS_Time.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_7ff_Accuracy_GPS_Time.Min = 0.0;
crt_PT_7ff_Accuracy_GPS_Time.Max = 255.0;
crt_PT_7ff_Accuracy_GPS_Time.DocUnits = '';
crt_PT_7ff_Accuracy_GPS_Time.Dimensions = 1;
crt_PT_7ff_Accuracy_GPS_Time.Complexity = 'real';
crt_PT_7ff_Accuracy_GPS_Time.SampleTime = -1;
crt_PT_7ff_Accuracy_GPS_Time.SamplingMode = 'Sample based';
crt_PT_7ff_Accuracy_GPS_Time.InitialValue = '';
% Signal crt_PT_7ff_GPS_Time
crt_PT_7ff_GPS_Time = Simulink.Signal;
crt_PT_7ff_GPS_Time.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_7ff_GPS_Time.RTWInfo.Alias = '';
crt_PT_7ff_GPS_Time.Description = ...
  ['GPS time is the time in seconds since midnight GMT on Saturday night.' char(10) ...
   'Frame: RT_SB_GPS_Time, 2047 (0x7ff).' char(10) ...
   'Signal: GPS_Time.' char(10) ...
   'Range (world values): 0.0 ... 604800.0 [s].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [s]' ...
  ];
crt_PT_7ff_GPS_Time.DataType = 'fixdt(0, 32, 0.001, 0.0)';
crt_PT_7ff_GPS_Time.Min = 0.0;
crt_PT_7ff_GPS_Time.Max = 604800.0;
crt_PT_7ff_GPS_Time.DocUnits = 's';
crt_PT_7ff_GPS_Time.Dimensions = 1;
crt_PT_7ff_GPS_Time.Complexity = 'real';
crt_PT_7ff_GPS_Time.SampleTime = -1;
crt_PT_7ff_GPS_Time.SamplingMode = 'Sample based';
crt_PT_7ff_GPS_Time.InitialValue = '';
% Signal crt_PT_7ff_GPS_Week
crt_PT_7ff_GPS_Week = Simulink.Signal;
crt_PT_7ff_GPS_Week.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_7ff_GPS_Week.RTWInfo.Alias = '';
crt_PT_7ff_GPS_Week.Description = ...
  ['Frame: RT_SB_GPS_Time, 2047 (0x7ff).' char(10) ...
   'Signal: GPS_Week.' char(10) ...
   'Range (world values): 0.0 ... 65535.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_7ff_GPS_Week.DataType = 'fixdt(0, 16, 1.0, 0.0)';
crt_PT_7ff_GPS_Week.Min = 0.0;
crt_PT_7ff_GPS_Week.Max = 65535.0;
crt_PT_7ff_GPS_Week.DocUnits = '';
crt_PT_7ff_GPS_Week.Dimensions = 1;
crt_PT_7ff_GPS_Week.Complexity = 'real';
crt_PT_7ff_GPS_Week.SampleTime = -1;
crt_PT_7ff_GPS_Week.SamplingMode = 'Sample based';
crt_PT_7ff_GPS_Week.InitialValue = '';

% Frame RT_SB_Accel, 290 (0x122)
% Signal crt_PT_122_Validity_Accel_Longitudinal
crt_PT_122_Validity_Accel_Longitudinal = Simulink.Signal;
crt_PT_122_Validity_Accel_Longitudinal.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_122_Validity_Accel_Longitudinal.RTWInfo.Alias = '';
crt_PT_122_Validity_Accel_Longitudinal.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Accel, 290 (0x122).' char(10) ...
   'Signal: Validity_Accel_Longitudinal.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_122_Validity_Accel_Longitudinal.DataType = 'boolean';
crt_PT_122_Validity_Accel_Longitudinal.Min = 0.0;
crt_PT_122_Validity_Accel_Longitudinal.Max = 1.0;
crt_PT_122_Validity_Accel_Longitudinal.DocUnits = '';
crt_PT_122_Validity_Accel_Longitudinal.Dimensions = 1;
crt_PT_122_Validity_Accel_Longitudinal.Complexity = 'real';
crt_PT_122_Validity_Accel_Longitudinal.SampleTime = -1;
crt_PT_122_Validity_Accel_Longitudinal.SamplingMode = 'Sample based';
crt_PT_122_Validity_Accel_Longitudinal.InitialValue = '';
% Signal crt_PT_122_Validity_Accel_Lateral
crt_PT_122_Validity_Accel_Lateral = Simulink.Signal;
crt_PT_122_Validity_Accel_Lateral.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_122_Validity_Accel_Lateral.RTWInfo.Alias = '';
crt_PT_122_Validity_Accel_Lateral.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Accel, 290 (0x122).' char(10) ...
   'Signal: Validity_Accel_Lateral.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_122_Validity_Accel_Lateral.DataType = 'boolean';
crt_PT_122_Validity_Accel_Lateral.Min = 0.0;
crt_PT_122_Validity_Accel_Lateral.Max = 1.0;
crt_PT_122_Validity_Accel_Lateral.DocUnits = '';
crt_PT_122_Validity_Accel_Lateral.Dimensions = 1;
crt_PT_122_Validity_Accel_Lateral.Complexity = 'real';
crt_PT_122_Validity_Accel_Lateral.SampleTime = -1;
crt_PT_122_Validity_Accel_Lateral.SamplingMode = 'Sample based';
crt_PT_122_Validity_Accel_Lateral.InitialValue = '';
% Signal crt_PT_122_Validity_Accel_Vertical
crt_PT_122_Validity_Accel_Vertical = Simulink.Signal;
crt_PT_122_Validity_Accel_Vertical.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_122_Validity_Accel_Vertical.RTWInfo.Alias = '';
crt_PT_122_Validity_Accel_Vertical.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Accel, 290 (0x122).' char(10) ...
   'Signal: Validity_Accel_Vertical.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_122_Validity_Accel_Vertical.DataType = 'boolean';
crt_PT_122_Validity_Accel_Vertical.Min = 0.0;
crt_PT_122_Validity_Accel_Vertical.Max = 1.0;
crt_PT_122_Validity_Accel_Vertical.DocUnits = '';
crt_PT_122_Validity_Accel_Vertical.Dimensions = 1;
crt_PT_122_Validity_Accel_Vertical.Complexity = 'real';
crt_PT_122_Validity_Accel_Vertical.SampleTime = -1;
crt_PT_122_Validity_Accel_Vertical.SamplingMode = 'Sample based';
crt_PT_122_Validity_Accel_Vertical.InitialValue = '';
% Signal crt_PT_122_Accuracy_Accel
crt_PT_122_Accuracy_Accel = Simulink.Signal;
crt_PT_122_Accuracy_Accel.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_122_Accuracy_Accel.RTWInfo.Alias = '';
crt_PT_122_Accuracy_Accel.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_Accel, 290 (0x122).' char(10) ...
   'Signal: Accuracy_Accel.' char(10) ...
   'Range (world values): 0.0 ... 255.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_122_Accuracy_Accel.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_122_Accuracy_Accel.Min = 0.0;
crt_PT_122_Accuracy_Accel.Max = 255.0;
crt_PT_122_Accuracy_Accel.DocUnits = '';
crt_PT_122_Accuracy_Accel.Dimensions = 1;
crt_PT_122_Accuracy_Accel.Complexity = 'real';
crt_PT_122_Accuracy_Accel.SampleTime = -1;
crt_PT_122_Accuracy_Accel.SamplingMode = 'Sample based';
crt_PT_122_Accuracy_Accel.InitialValue = '';
% Signal crt_PT_122_Accel_Longitudinal
crt_PT_122_Accel_Longitudinal = Simulink.Signal;
crt_PT_122_Accel_Longitudinal.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_122_Accel_Longitudinal.RTWInfo.Alias = '';
crt_PT_122_Accel_Longitudinal.Description = ...
  ['Longitudinal acceleration.  This is positive when the vehicle accelerates in a forwards direction.' char(10) ...
   'Frame: RT_SB_Accel, 290 (0x122).' char(10) ...
   'Signal: Accel_Longitudinal.' char(10) ...
   'Range (world values): -65.0 ... 65.0 [g].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [g]' ...
  ];
crt_PT_122_Accel_Longitudinal.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_122_Accel_Longitudinal.Min = -65.0;
crt_PT_122_Accel_Longitudinal.Max = 65.0;
crt_PT_122_Accel_Longitudinal.DocUnits = 'g';
crt_PT_122_Accel_Longitudinal.Dimensions = 1;
crt_PT_122_Accel_Longitudinal.Complexity = 'real';
crt_PT_122_Accel_Longitudinal.SampleTime = -1;
crt_PT_122_Accel_Longitudinal.SamplingMode = 'Sample based';
crt_PT_122_Accel_Longitudinal.InitialValue = '';
% Signal crt_PT_122_Accel_Lateral
crt_PT_122_Accel_Lateral = Simulink.Signal;
crt_PT_122_Accel_Lateral.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_122_Accel_Lateral.RTWInfo.Alias = '';
crt_PT_122_Accel_Lateral.Description = ...
  ['Lateral acceleration.  This is positive when the vehicle accelerates towards the right, e.g. when cornering around a right-hand bend.' char(10) ...
   'Frame: RT_SB_Accel, 290 (0x122).' char(10) ...
   'Signal: Accel_Lateral.' char(10) ...
   'Range (world values): -65.0 ... 65.0 [g].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [g]' ...
  ];
crt_PT_122_Accel_Lateral.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_122_Accel_Lateral.Min = -65.0;
crt_PT_122_Accel_Lateral.Max = 65.0;
crt_PT_122_Accel_Lateral.DocUnits = 'g';
crt_PT_122_Accel_Lateral.Dimensions = 1;
crt_PT_122_Accel_Lateral.Complexity = 'real';
crt_PT_122_Accel_Lateral.SampleTime = -1;
crt_PT_122_Accel_Lateral.SamplingMode = 'Sample based';
crt_PT_122_Accel_Lateral.InitialValue = '';
% Signal crt_PT_122_Accel_Vertical
crt_PT_122_Accel_Vertical = Simulink.Signal;
crt_PT_122_Accel_Vertical.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_122_Accel_Vertical.RTWInfo.Alias = '';
crt_PT_122_Accel_Vertical.Description = ...
  ['Vertical acceleration.  This is positive when the vehicle accelerates in an upwards direction, e.g. when travelling through a dip.' char(10) ...
   'Frame: RT_SB_Accel, 290 (0x122).' char(10) ...
   'Signal: Accel_Vertical.' char(10) ...
   'Range (world values): -65.0 ... 65.0 [g].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [g]' ...
  ];
crt_PT_122_Accel_Vertical.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_122_Accel_Vertical.Min = -65.0;
crt_PT_122_Accel_Vertical.Max = 65.0;
crt_PT_122_Accel_Vertical.DocUnits = 'g';
crt_PT_122_Accel_Vertical.Dimensions = 1;
crt_PT_122_Accel_Vertical.Complexity = 'real';
crt_PT_122_Accel_Vertical.SampleTime = -1;
crt_PT_122_Accel_Vertical.SamplingMode = 'Sample based';
crt_PT_122_Accel_Vertical.InitialValue = '';

% Frame RT_SB_Gyro_Rates, 8388898 (0x800122)
% Signal crt_PT_800122_Validity_Gyro_Rate_Yaw
crt_PT_800122_Validity_Gyro_Rate_Yaw = Simulink.Signal;
crt_PT_800122_Validity_Gyro_Rate_Yaw.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800122_Validity_Gyro_Rate_Yaw.RTWInfo.Alias = '';
crt_PT_800122_Validity_Gyro_Rate_Yaw.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Gyro_Rates, 8388898 (0x800122).' char(10) ...
   'Signal: Validity_Gyro_Rate_Yaw.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800122_Validity_Gyro_Rate_Yaw.DataType = 'boolean';
crt_PT_800122_Validity_Gyro_Rate_Yaw.Min = 0.0;
crt_PT_800122_Validity_Gyro_Rate_Yaw.Max = 1.0;
crt_PT_800122_Validity_Gyro_Rate_Yaw.DocUnits = '';
crt_PT_800122_Validity_Gyro_Rate_Yaw.Dimensions = 1;
crt_PT_800122_Validity_Gyro_Rate_Yaw.Complexity = 'real';
crt_PT_800122_Validity_Gyro_Rate_Yaw.SampleTime = -1;
crt_PT_800122_Validity_Gyro_Rate_Yaw.SamplingMode = 'Sample based';
crt_PT_800122_Validity_Gyro_Rate_Yaw.InitialValue = '';
% Signal crt_PT_800122_Validity_Gyro_Rate_Pitch
crt_PT_800122_Validity_Gyro_Rate_Pitch = Simulink.Signal;
crt_PT_800122_Validity_Gyro_Rate_Pitch.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800122_Validity_Gyro_Rate_Pitch.RTWInfo.Alias = '';
crt_PT_800122_Validity_Gyro_Rate_Pitch.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Gyro_Rates, 8388898 (0x800122).' char(10) ...
   'Signal: Validity_Gyro_Rate_Pitch.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800122_Validity_Gyro_Rate_Pitch.DataType = 'boolean';
crt_PT_800122_Validity_Gyro_Rate_Pitch.Min = 0.0;
crt_PT_800122_Validity_Gyro_Rate_Pitch.Max = 1.0;
crt_PT_800122_Validity_Gyro_Rate_Pitch.DocUnits = '';
crt_PT_800122_Validity_Gyro_Rate_Pitch.Dimensions = 1;
crt_PT_800122_Validity_Gyro_Rate_Pitch.Complexity = 'real';
crt_PT_800122_Validity_Gyro_Rate_Pitch.SampleTime = -1;
crt_PT_800122_Validity_Gyro_Rate_Pitch.SamplingMode = 'Sample based';
crt_PT_800122_Validity_Gyro_Rate_Pitch.InitialValue = '';
% Signal crt_PT_800122_Validity_Gyro_Rate_Roll
crt_PT_800122_Validity_Gyro_Rate_Roll = Simulink.Signal;
crt_PT_800122_Validity_Gyro_Rate_Roll.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800122_Validity_Gyro_Rate_Roll.RTWInfo.Alias = '';
crt_PT_800122_Validity_Gyro_Rate_Roll.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Gyro_Rates, 8388898 (0x800122).' char(10) ...
   'Signal: Validity_Gyro_Rate_Roll.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800122_Validity_Gyro_Rate_Roll.DataType = 'boolean';
crt_PT_800122_Validity_Gyro_Rate_Roll.Min = 0.0;
crt_PT_800122_Validity_Gyro_Rate_Roll.Max = 1.0;
crt_PT_800122_Validity_Gyro_Rate_Roll.DocUnits = '';
crt_PT_800122_Validity_Gyro_Rate_Roll.Dimensions = 1;
crt_PT_800122_Validity_Gyro_Rate_Roll.Complexity = 'real';
crt_PT_800122_Validity_Gyro_Rate_Roll.SampleTime = -1;
crt_PT_800122_Validity_Gyro_Rate_Roll.SamplingMode = 'Sample based';
crt_PT_800122_Validity_Gyro_Rate_Roll.InitialValue = '';
% Signal crt_PT_800122_Accuracy_Gyro_Rates
crt_PT_800122_Accuracy_Gyro_Rates = Simulink.Signal;
crt_PT_800122_Accuracy_Gyro_Rates.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800122_Accuracy_Gyro_Rates.RTWInfo.Alias = '';
crt_PT_800122_Accuracy_Gyro_Rates.Description = ...
  ['Dimensionless.  Lower values imply but do not guarantee better accuracy than higher values.' char(10) ...
   'Frame: RT_SB_Gyro_Rates, 8388898 (0x800122).' char(10) ...
   'Signal: Accuracy_Gyro_Rates.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_800122_Accuracy_Gyro_Rates.DataType = 'fixdt(0, 8,  1.0, 0.0)';
crt_PT_800122_Accuracy_Gyro_Rates.Min = 0.0;
crt_PT_800122_Accuracy_Gyro_Rates.Max = 0.0;
crt_PT_800122_Accuracy_Gyro_Rates.DocUnits = '';
crt_PT_800122_Accuracy_Gyro_Rates.Dimensions = 1;
crt_PT_800122_Accuracy_Gyro_Rates.Complexity = 'real';
crt_PT_800122_Accuracy_Gyro_Rates.SampleTime = -1;
crt_PT_800122_Accuracy_Gyro_Rates.SamplingMode = 'Sample based';
crt_PT_800122_Accuracy_Gyro_Rates.InitialValue = '';
% Signal crt_PT_800122_Gyro_Rate_Yaw
crt_PT_800122_Gyro_Rate_Yaw = Simulink.Signal;
crt_PT_800122_Gyro_Rate_Yaw.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800122_Gyro_Rate_Yaw.RTWInfo.Alias = '';
crt_PT_800122_Gyro_Rate_Yaw.Description = ...
  ['Yaw rate is positive for clockwise rotation when looking down on the vehicle from above.' char(10) ...
   'Frame: RT_SB_Gyro_Rates, 8388898 (0x800122).' char(10) ...
   'Signal: Gyro_Rate_Yaw.' char(10) ...
   'Range (world values): -327.0 ... 327.0 [degrees/s].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees/s]' ...
  ];
crt_PT_800122_Gyro_Rate_Yaw.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_800122_Gyro_Rate_Yaw.Min = -327.0;
crt_PT_800122_Gyro_Rate_Yaw.Max = 327.0;
crt_PT_800122_Gyro_Rate_Yaw.DocUnits = 'degrees/s';
crt_PT_800122_Gyro_Rate_Yaw.Dimensions = 1;
crt_PT_800122_Gyro_Rate_Yaw.Complexity = 'real';
crt_PT_800122_Gyro_Rate_Yaw.SampleTime = -1;
crt_PT_800122_Gyro_Rate_Yaw.SamplingMode = 'Sample based';
crt_PT_800122_Gyro_Rate_Yaw.InitialValue = '';
% Signal crt_PT_800122_Gyro_Rate_Pitch
crt_PT_800122_Gyro_Rate_Pitch = Simulink.Signal;
crt_PT_800122_Gyro_Rate_Pitch.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800122_Gyro_Rate_Pitch.RTWInfo.Alias = '';
crt_PT_800122_Gyro_Rate_Pitch.Description = ...
  ['Pitch rate is positive for clockwise rotation when looking at the left hand side of the vehicle from the left of the vehicle.' char(10) ...
   'Frame: RT_SB_Gyro_Rates, 8388898 (0x800122).' char(10) ...
   'Signal: Gyro_Rate_Pitch.' char(10) ...
   'Range (world values): -327.0 ... 327.0 [degrees/s].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees/s]' ...
  ];
crt_PT_800122_Gyro_Rate_Pitch.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_800122_Gyro_Rate_Pitch.Min = -327.0;
crt_PT_800122_Gyro_Rate_Pitch.Max = 327.0;
crt_PT_800122_Gyro_Rate_Pitch.DocUnits = 'degrees/s';
crt_PT_800122_Gyro_Rate_Pitch.Dimensions = 1;
crt_PT_800122_Gyro_Rate_Pitch.Complexity = 'real';
crt_PT_800122_Gyro_Rate_Pitch.SampleTime = -1;
crt_PT_800122_Gyro_Rate_Pitch.SamplingMode = 'Sample based';
crt_PT_800122_Gyro_Rate_Pitch.InitialValue = '';
% Signal crt_PT_800122_Gyro_Rate_Roll
crt_PT_800122_Gyro_Rate_Roll = Simulink.Signal;
crt_PT_800122_Gyro_Rate_Roll.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_800122_Gyro_Rate_Roll.RTWInfo.Alias = '';
crt_PT_800122_Gyro_Rate_Roll.Description = ...
  ['Roll rate is positive for clockwise rotation when looking at the rear of the vehicle from behind the vehicle.' char(10) ...
   'Frame: RT_SB_Gyro_Rates, 8388898 (0x800122).' char(10) ...
   'Signal: Gyro_Rate_Roll.' char(10) ...
   'Range (world values): -327.0 ... 327.0 [degrees/s].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [degrees/s]' ...
  ];
crt_PT_800122_Gyro_Rate_Roll.DataType = 'fixdt(1, 16, 0.01, 0.0)';
crt_PT_800122_Gyro_Rate_Roll.Min = -327.0;
crt_PT_800122_Gyro_Rate_Roll.Max = 327.0;
crt_PT_800122_Gyro_Rate_Roll.DocUnits = 'degrees/s';
crt_PT_800122_Gyro_Rate_Roll.Dimensions = 1;
crt_PT_800122_Gyro_Rate_Roll.Complexity = 'real';
crt_PT_800122_Gyro_Rate_Roll.SampleTime = -1;
crt_PT_800122_Gyro_Rate_Roll.SamplingMode = 'Sample based';
crt_PT_800122_Gyro_Rate_Roll.InitialValue = '';

% Sent Frames

% Frame RT_IRTemp_Temp_RL_2, 9963045 (0x980625)
% Signal crt_PT_980625_IR_Temperature_21
crt_PT_980625_IR_Temperature_21 = Simulink.Signal;
crt_PT_980625_IR_Temperature_21.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980625_IR_Temperature_21.RTWInfo.Alias = '';
crt_PT_980625_IR_Temperature_21.Description = ...
  ['Frame: RT_IRTemp_Temp_RL_2, 9963045 (0x980625).' char(10) ...
   'Signal: IR_Temperature_21.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980625_IR_Temperature_21.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980625_IR_Temperature_21.Min = 0.0;
crt_PT_980625_IR_Temperature_21.Max = 0.0;
crt_PT_980625_IR_Temperature_21.DocUnits = '';
crt_PT_980625_IR_Temperature_21.Dimensions = 1;
crt_PT_980625_IR_Temperature_21.Complexity = 'real';
crt_PT_980625_IR_Temperature_21.SampleTime = -1;
crt_PT_980625_IR_Temperature_21.SamplingMode = 'Sample based';
crt_PT_980625_IR_Temperature_21.InitialValue = '';
% Signal crt_PT_980625_IR_Temperature_22
crt_PT_980625_IR_Temperature_22 = Simulink.Signal;
crt_PT_980625_IR_Temperature_22.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980625_IR_Temperature_22.RTWInfo.Alias = '';
crt_PT_980625_IR_Temperature_22.Description = ...
  ['Frame: RT_IRTemp_Temp_RL_2, 9963045 (0x980625).' char(10) ...
   'Signal: IR_Temperature_22.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980625_IR_Temperature_22.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980625_IR_Temperature_22.Min = 0.0;
crt_PT_980625_IR_Temperature_22.Max = 0.0;
crt_PT_980625_IR_Temperature_22.DocUnits = '';
crt_PT_980625_IR_Temperature_22.Dimensions = 1;
crt_PT_980625_IR_Temperature_22.Complexity = 'real';
crt_PT_980625_IR_Temperature_22.SampleTime = -1;
crt_PT_980625_IR_Temperature_22.SamplingMode = 'Sample based';
crt_PT_980625_IR_Temperature_22.InitialValue = '';
% Signal crt_PT_980625_IR_Temperature_23
crt_PT_980625_IR_Temperature_23 = Simulink.Signal;
crt_PT_980625_IR_Temperature_23.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980625_IR_Temperature_23.RTWInfo.Alias = '';
crt_PT_980625_IR_Temperature_23.Description = ...
  ['Frame: RT_IRTemp_Temp_RL_2, 9963045 (0x980625).' char(10) ...
   'Signal: IR_Temperature_23.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980625_IR_Temperature_23.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980625_IR_Temperature_23.Min = 0.0;
crt_PT_980625_IR_Temperature_23.Max = 0.0;
crt_PT_980625_IR_Temperature_23.DocUnits = '';
crt_PT_980625_IR_Temperature_23.Dimensions = 1;
crt_PT_980625_IR_Temperature_23.Complexity = 'real';
crt_PT_980625_IR_Temperature_23.SampleTime = -1;
crt_PT_980625_IR_Temperature_23.SamplingMode = 'Sample based';
crt_PT_980625_IR_Temperature_23.InitialValue = '';
% Signal crt_PT_980625_IR_Temperature_24
crt_PT_980625_IR_Temperature_24 = Simulink.Signal;
crt_PT_980625_IR_Temperature_24.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980625_IR_Temperature_24.RTWInfo.Alias = '';
crt_PT_980625_IR_Temperature_24.Description = ...
  ['Frame: RT_IRTemp_Temp_RL_2, 9963045 (0x980625).' char(10) ...
   'Signal: IR_Temperature_24.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980625_IR_Temperature_24.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980625_IR_Temperature_24.Min = 0.0;
crt_PT_980625_IR_Temperature_24.Max = 0.0;
crt_PT_980625_IR_Temperature_24.DocUnits = '';
crt_PT_980625_IR_Temperature_24.Dimensions = 1;
crt_PT_980625_IR_Temperature_24.Complexity = 'real';
crt_PT_980625_IR_Temperature_24.SampleTime = -1;
crt_PT_980625_IR_Temperature_24.SamplingMode = 'Sample based';
crt_PT_980625_IR_Temperature_24.InitialValue = '';

% Frame RT_IRTemp_Temp_FR_2, 9962533 (0x980425)
% Signal crt_PT_980425_IR_Temperature_13
crt_PT_980425_IR_Temperature_13 = Simulink.Signal;
crt_PT_980425_IR_Temperature_13.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980425_IR_Temperature_13.RTWInfo.Alias = '';
crt_PT_980425_IR_Temperature_13.Description = ...
  ['Frame: RT_IRTemp_Temp_FR_2, 9962533 (0x980425).' char(10) ...
   'Signal: IR_Temperature_13.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980425_IR_Temperature_13.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980425_IR_Temperature_13.Min = 0.0;
crt_PT_980425_IR_Temperature_13.Max = 0.0;
crt_PT_980425_IR_Temperature_13.DocUnits = '';
crt_PT_980425_IR_Temperature_13.Dimensions = 1;
crt_PT_980425_IR_Temperature_13.Complexity = 'real';
crt_PT_980425_IR_Temperature_13.SampleTime = -1;
crt_PT_980425_IR_Temperature_13.SamplingMode = 'Sample based';
crt_PT_980425_IR_Temperature_13.InitialValue = '';
% Signal crt_PT_980425_IR_Temperature_14
crt_PT_980425_IR_Temperature_14 = Simulink.Signal;
crt_PT_980425_IR_Temperature_14.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980425_IR_Temperature_14.RTWInfo.Alias = '';
crt_PT_980425_IR_Temperature_14.Description = ...
  ['Frame: RT_IRTemp_Temp_FR_2, 9962533 (0x980425).' char(10) ...
   'Signal: IR_Temperature_14.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980425_IR_Temperature_14.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980425_IR_Temperature_14.Min = 0.0;
crt_PT_980425_IR_Temperature_14.Max = 0.0;
crt_PT_980425_IR_Temperature_14.DocUnits = '';
crt_PT_980425_IR_Temperature_14.Dimensions = 1;
crt_PT_980425_IR_Temperature_14.Complexity = 'real';
crt_PT_980425_IR_Temperature_14.SampleTime = -1;
crt_PT_980425_IR_Temperature_14.SamplingMode = 'Sample based';
crt_PT_980425_IR_Temperature_14.InitialValue = '';
% Signal crt_PT_980425_IR_Temperature_15
crt_PT_980425_IR_Temperature_15 = Simulink.Signal;
crt_PT_980425_IR_Temperature_15.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980425_IR_Temperature_15.RTWInfo.Alias = '';
crt_PT_980425_IR_Temperature_15.Description = ...
  ['Frame: RT_IRTemp_Temp_FR_2, 9962533 (0x980425).' char(10) ...
   'Signal: IR_Temperature_15.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980425_IR_Temperature_15.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980425_IR_Temperature_15.Min = 0.0;
crt_PT_980425_IR_Temperature_15.Max = 0.0;
crt_PT_980425_IR_Temperature_15.DocUnits = '';
crt_PT_980425_IR_Temperature_15.Dimensions = 1;
crt_PT_980425_IR_Temperature_15.Complexity = 'real';
crt_PT_980425_IR_Temperature_15.SampleTime = -1;
crt_PT_980425_IR_Temperature_15.SamplingMode = 'Sample based';
crt_PT_980425_IR_Temperature_15.InitialValue = '';
% Signal crt_PT_980425_IR_Temperature_16
crt_PT_980425_IR_Temperature_16 = Simulink.Signal;
crt_PT_980425_IR_Temperature_16.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_980425_IR_Temperature_16.RTWInfo.Alias = '';
crt_PT_980425_IR_Temperature_16.Description = ...
  ['Frame: RT_IRTemp_Temp_FR_2, 9962533 (0x980425).' char(10) ...
   'Signal: IR_Temperature_16.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_980425_IR_Temperature_16.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_980425_IR_Temperature_16.Min = 0.0;
crt_PT_980425_IR_Temperature_16.Max = 0.0;
crt_PT_980425_IR_Temperature_16.DocUnits = '';
crt_PT_980425_IR_Temperature_16.Dimensions = 1;
crt_PT_980425_IR_Temperature_16.Complexity = 'real';
crt_PT_980425_IR_Temperature_16.SampleTime = -1;
crt_PT_980425_IR_Temperature_16.SamplingMode = 'Sample based';
crt_PT_980425_IR_Temperature_16.InitialValue = '';

% Frame RT_IRTemp_Temp_30, 9510437 (0x911e25)
% Signal crt_PT_911e25_IR_Temperature_30
crt_PT_911e25_IR_Temperature_30 = Simulink.Signal;
crt_PT_911e25_IR_Temperature_30.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911e25_IR_Temperature_30.RTWInfo.Alias = '';
crt_PT_911e25_IR_Temperature_30.Description = ...
  ['Frame: RT_IRTemp_Temp_30, 9510437 (0x911e25).' char(10) ...
   'Signal: IR_Temperature_30.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911e25_IR_Temperature_30.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911e25_IR_Temperature_30.Min = 0.0;
crt_PT_911e25_IR_Temperature_30.Max = 0.0;
crt_PT_911e25_IR_Temperature_30.DocUnits = '';
crt_PT_911e25_IR_Temperature_30.Dimensions = 1;
crt_PT_911e25_IR_Temperature_30.Complexity = 'real';
crt_PT_911e25_IR_Temperature_30.SampleTime = -1;
crt_PT_911e25_IR_Temperature_30.SamplingMode = 'Sample based';
crt_PT_911e25_IR_Temperature_30.InitialValue = '';

% Frame RT_IRTemp_Temp_26, 9509413 (0x911a25)
% Signal crt_PT_911a25_IR_Temperature_26
crt_PT_911a25_IR_Temperature_26 = Simulink.Signal;
crt_PT_911a25_IR_Temperature_26.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_911a25_IR_Temperature_26.RTWInfo.Alias = '';
crt_PT_911a25_IR_Temperature_26.Description = ...
  ['Frame: RT_IRTemp_Temp_26, 9509413 (0x911a25).' char(10) ...
   'Signal: IR_Temperature_26.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_911a25_IR_Temperature_26.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_911a25_IR_Temperature_26.Min = 0.0;
crt_PT_911a25_IR_Temperature_26.Max = 0.0;
crt_PT_911a25_IR_Temperature_26.DocUnits = '';
crt_PT_911a25_IR_Temperature_26.Dimensions = 1;
crt_PT_911a25_IR_Temperature_26.Complexity = 'real';
crt_PT_911a25_IR_Temperature_26.SampleTime = -1;
crt_PT_911a25_IR_Temperature_26.SamplingMode = 'Sample based';
crt_PT_911a25_IR_Temperature_26.InitialValue = '';

% Frame RT_SB_Trig_Forward_Dist, 9241634 (0x8d0422)
% Signal crt_PT_8d0422_Forward_Distance
crt_PT_8d0422_Forward_Distance = Simulink.Signal;
crt_PT_8d0422_Forward_Distance.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0422_Forward_Distance.RTWInfo.Alias = '';
crt_PT_8d0422_Forward_Distance.Description = ...
  ['Current forward distance from start of test in direction of initial heading at start of test' char(10) ...
   'Frame: RT_SB_Trig_Forward_Dist, 9241634 (0x8d0422).' char(10) ...
   'Signal: Forward_Distance.' char(10) ...
   'Range (world values): -2147480.0 ... 2147480.0 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8d0422_Forward_Distance.DataType = 'fixdt(1, 32, 0.001, 0.0)';
crt_PT_8d0422_Forward_Distance.Min = -2147480.0;
crt_PT_8d0422_Forward_Distance.Max = 2147480.0;
crt_PT_8d0422_Forward_Distance.DocUnits = 'm';
crt_PT_8d0422_Forward_Distance.Dimensions = 1;
crt_PT_8d0422_Forward_Distance.Complexity = 'real';
crt_PT_8d0422_Forward_Distance.SampleTime = -1;
crt_PT_8d0422_Forward_Distance.SamplingMode = 'Sample based';
crt_PT_8d0422_Forward_Distance.InitialValue = '';
% Signal crt_PT_8d0422_Deviation_Distance
crt_PT_8d0422_Deviation_Distance = Simulink.Signal;
crt_PT_8d0422_Deviation_Distance.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0422_Deviation_Distance.RTWInfo.Alias = '';
crt_PT_8d0422_Deviation_Distance.Description = ...
  ['Current deviation distance from a line projected along the initial heading at start of test, +ve for deviation to the right.' char(10) ...
   'Frame: RT_SB_Trig_Forward_Dist, 9241634 (0x8d0422).' char(10) ...
   'Signal: Deviation_Distance.' char(10) ...
   'Range (world values): -2147480.0 ... 2147480.0 [m].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [m]' ...
  ];
crt_PT_8d0422_Deviation_Distance.DataType = 'fixdt(1, 32, 0.001, 0.0)';
crt_PT_8d0422_Deviation_Distance.Min = -2147480.0;
crt_PT_8d0422_Deviation_Distance.Max = 2147480.0;
crt_PT_8d0422_Deviation_Distance.DocUnits = 'm';
crt_PT_8d0422_Deviation_Distance.Dimensions = 1;
crt_PT_8d0422_Deviation_Distance.Complexity = 'real';
crt_PT_8d0422_Deviation_Distance.SampleTime = -1;
crt_PT_8d0422_Deviation_Distance.SamplingMode = 'Sample based';
crt_PT_8d0422_Deviation_Distance.InitialValue = '';

% Frame RT_SB_Trig_Accel, 9241122 (0x8d0222)
% Signal crt_PT_8d0222_Validity_MFDD
crt_PT_8d0222_Validity_MFDD = Simulink.Signal;
crt_PT_8d0222_Validity_MFDD.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0222_Validity_MFDD.RTWInfo.Alias = '';
crt_PT_8d0222_Validity_MFDD.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Trig_Accel, 9241122 (0x8d0222).' char(10) ...
   'Signal: Validity_MFDD.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8d0222_Validity_MFDD.DataType = 'boolean';
crt_PT_8d0222_Validity_MFDD.Min = 0.0;
crt_PT_8d0222_Validity_MFDD.Max = 1.0;
crt_PT_8d0222_Validity_MFDD.DocUnits = '';
crt_PT_8d0222_Validity_MFDD.Dimensions = 1;
crt_PT_8d0222_Validity_MFDD.Complexity = 'real';
crt_PT_8d0222_Validity_MFDD.SampleTime = -1;
crt_PT_8d0222_Validity_MFDD.SamplingMode = 'Sample based';
crt_PT_8d0222_Validity_MFDD.InitialValue = '';
% Signal crt_PT_8d0222_Validity_Average_Accel
crt_PT_8d0222_Validity_Average_Accel = Simulink.Signal;
crt_PT_8d0222_Validity_Average_Accel.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0222_Validity_Average_Accel.RTWInfo.Alias = '';
crt_PT_8d0222_Validity_Average_Accel.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Trig_Accel, 9241122 (0x8d0222).' char(10) ...
   'Signal: Validity_Average_Accel.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8d0222_Validity_Average_Accel.DataType = 'boolean';
crt_PT_8d0222_Validity_Average_Accel.Min = 0.0;
crt_PT_8d0222_Validity_Average_Accel.Max = 1.0;
crt_PT_8d0222_Validity_Average_Accel.DocUnits = '';
crt_PT_8d0222_Validity_Average_Accel.Dimensions = 1;
crt_PT_8d0222_Validity_Average_Accel.Complexity = 'real';
crt_PT_8d0222_Validity_Average_Accel.SampleTime = -1;
crt_PT_8d0222_Validity_Average_Accel.SamplingMode = 'Sample based';
crt_PT_8d0222_Validity_Average_Accel.InitialValue = '';
% Signal crt_PT_8d0222_Validity_Triggered_Time
crt_PT_8d0222_Validity_Triggered_Time = Simulink.Signal;
crt_PT_8d0222_Validity_Triggered_Time.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0222_Validity_Triggered_Time.RTWInfo.Alias = '';
crt_PT_8d0222_Validity_Triggered_Time.Description = ...
  ['Valid when bit is set, invalid when bit is clear.' char(10) ...
   'Frame: RT_SB_Trig_Accel, 9241122 (0x8d0222).' char(10) ...
   'Signal: Validity_Triggered_Time.' char(10) ...
   'Range (world values): 0.0 ... 1.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_8d0222_Validity_Triggered_Time.DataType = 'boolean';
crt_PT_8d0222_Validity_Triggered_Time.Min = 0.0;
crt_PT_8d0222_Validity_Triggered_Time.Max = 1.0;
crt_PT_8d0222_Validity_Triggered_Time.DocUnits = '';
crt_PT_8d0222_Validity_Triggered_Time.Dimensions = 1;
crt_PT_8d0222_Validity_Triggered_Time.Complexity = 'real';
crt_PT_8d0222_Validity_Triggered_Time.SampleTime = -1;
crt_PT_8d0222_Validity_Triggered_Time.SamplingMode = 'Sample based';
crt_PT_8d0222_Validity_Triggered_Time.InitialValue = '';
% Signal crt_PT_8d0222_MFDD
crt_PT_8d0222_MFDD = Simulink.Signal;
crt_PT_8d0222_MFDD.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0222_MFDD.RTWInfo.Alias = '';
crt_PT_8d0222_MFDD.Description = ...
  ['Mean fully-developed decelleration of triggered test.  Thresholds used are as set in the logger configuration.' char(10) ...
   'Frame: RT_SB_Trig_Accel, 9241122 (0x8d0222).' char(10) ...
   'Signal: MFDD.' char(10) ...
   'Range (world values): -65.0 ... 65.0 [g].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [g]' ...
  ];
crt_PT_8d0222_MFDD.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_8d0222_MFDD.Min = -65.0;
crt_PT_8d0222_MFDD.Max = 65.0;
crt_PT_8d0222_MFDD.DocUnits = 'g';
crt_PT_8d0222_MFDD.Dimensions = 1;
crt_PT_8d0222_MFDD.Complexity = 'real';
crt_PT_8d0222_MFDD.SampleTime = -1;
crt_PT_8d0222_MFDD.SamplingMode = 'Sample based';
crt_PT_8d0222_MFDD.InitialValue = '';
% Signal crt_PT_8d0222_Average_Accel
crt_PT_8d0222_Average_Accel = Simulink.Signal;
crt_PT_8d0222_Average_Accel.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0222_Average_Accel.RTWInfo.Alias = '';
crt_PT_8d0222_Average_Accel.Description = ...
  ['Average acceleration from start of triggered test to current time.' char(10) ...
   'Frame: RT_SB_Trig_Accel, 9241122 (0x8d0222).' char(10) ...
   'Signal: Average_Accel.' char(10) ...
   'Range (world values): -65.0 ... 65.0 [g].' char(10) ...
   'Scaling: WorldValue = 0.001*BinaryValue + 0.0 [g]' ...
  ];
crt_PT_8d0222_Average_Accel.DataType = 'fixdt(1, 16, 0.001, 0.0)';
crt_PT_8d0222_Average_Accel.Min = -65.0;
crt_PT_8d0222_Average_Accel.Max = 65.0;
crt_PT_8d0222_Average_Accel.DocUnits = 'g';
crt_PT_8d0222_Average_Accel.Dimensions = 1;
crt_PT_8d0222_Average_Accel.Complexity = 'real';
crt_PT_8d0222_Average_Accel.SampleTime = -1;
crt_PT_8d0222_Average_Accel.SamplingMode = 'Sample based';
crt_PT_8d0222_Average_Accel.InitialValue = '';
% Signal crt_PT_8d0222_Triggered_Time
crt_PT_8d0222_Triggered_Time = Simulink.Signal;
crt_PT_8d0222_Triggered_Time.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_8d0222_Triggered_Time.RTWInfo.Alias = '';
crt_PT_8d0222_Triggered_Time.Description = ...
  ['Cumulative time from start of triggered test to current time.' char(10) ...
   'Frame: RT_SB_Trig_Accel, 9241122 (0x8d0222).' char(10) ...
   'Signal: Triggered_Time.' char(10) ...
   'Range (world values): 0.0 ... 167772.0 [s].' char(10) ...
   'Scaling: WorldValue = 0.01*BinaryValue + 0.0 [s]' ...
  ];
crt_PT_8d0222_Triggered_Time.DataType = 'fixdt(0, 32, 0.01, 0.0)';
crt_PT_8d0222_Triggered_Time.Min = 0.0;
crt_PT_8d0222_Triggered_Time.Max = 167772.0;
crt_PT_8d0222_Triggered_Time.DocUnits = 's';
crt_PT_8d0222_Triggered_Time.Dimensions = 1;
crt_PT_8d0222_Triggered_Time.Complexity = 'real';
crt_PT_8d0222_Triggered_Time.SampleTime = -1;
crt_PT_8d0222_Triggered_Time.SamplingMode = 'Sample based';
crt_PT_8d0222_Triggered_Time.InitialValue = '';

% Unused Frames

% Frame RT_IRTemp_Temp_7, 9504549 (0x910725)
% Signal crt_PT_910725_IR_Temperature_7
crt_PT_910725_IR_Temperature_7 = Simulink.Signal;
crt_PT_910725_IR_Temperature_7.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_910725_IR_Temperature_7.RTWInfo.Alias = '';
crt_PT_910725_IR_Temperature_7.Description = ...
  ['Frame: RT_IRTemp_Temp_7, 9504549 (0x910725).' char(10) ...
   'Signal: IR_Temperature_7.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = 0.1*BinaryValue + 0.0 []' ...
  ];
crt_PT_910725_IR_Temperature_7.DataType = 'fixdt(1, 16, 0.1, 0.0)';
crt_PT_910725_IR_Temperature_7.Min = 0.0;
crt_PT_910725_IR_Temperature_7.Max = 0.0;
crt_PT_910725_IR_Temperature_7.DocUnits = '';
crt_PT_910725_IR_Temperature_7.Dimensions = 1;
crt_PT_910725_IR_Temperature_7.Complexity = 'real';
crt_PT_910725_IR_Temperature_7.SampleTime = -1;
crt_PT_910725_IR_Temperature_7.SamplingMode = 'Sample based';
crt_PT_910725_IR_Temperature_7.InitialValue = '';

% Frame RT_DL1MK3_Measure_Time_12, 9833508 (0x960c24)
% Signal crt_PT_960c24_Measured_Time_12
crt_PT_960c24_Measured_Time_12 = Simulink.Signal;
crt_PT_960c24_Measured_Time_12.RTWInfo.StorageClass = 'ImportedExtern';
crt_PT_960c24_Measured_Time_12.RTWInfo.Alias = '';
crt_PT_960c24_Measured_Time_12.Description = ...
  ['Frame: RT_DL1MK3_Measure_Time_12, 9833508 (0x960c24).' char(10) ...
   'Signal: Measured_Time_12.' char(10) ...
   'Range (world values): 0.0 ... 0.0 [].' char(10) ...
   'Scaling: WorldValue = BinaryValue []' ...
  ];
crt_PT_960c24_Measured_Time_12.DataType = 'fixdt(0, 32, 1.0, 0.0)';
crt_PT_960c24_Measured_Time_12.Min = 0.0;
crt_PT_960c24_Measured_Time_12.Max = 0.0;
crt_PT_960c24_Measured_Time_12.DocUnits = '';
crt_PT_960c24_Measured_Time_12.Dimensions = 1;
crt_PT_960c24_Measured_Time_12.Complexity = 'real';
crt_PT_960c24_Measured_Time_12.SampleTime = -1;
crt_PT_960c24_Measured_Time_12.SamplingMode = 'Sample based';
crt_PT_960c24_Measured_Time_12.InitialValue = '';

