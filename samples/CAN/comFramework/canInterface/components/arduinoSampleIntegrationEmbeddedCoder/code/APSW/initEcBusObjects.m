% MATLAB script initEcBusObjects.m
% 
% This file implements the MATLAB readable specification of the data oriented CAN API
% between the Embedded Coder generated APSW code and the upper layers of the CAN stack. The
% specification is understood by the Embedded Coder and makes it generate code that
% directly links to the CAN API.
%   MATLAB reads this script as initialization of the Simulink model. A number of Simulink
% objects is created in the global workspace, which can be attached to a Simulink model in
% order to configure the code generation from this model with the Embedded Coder. The
% following objects are created:
%   A Simulink.Bus object is offered for each CAN bus. All signals from this bus are
% contained, which are either received or transmitted by the network node the software is
% running on. The bus is structured, each frame forms a sub-bus with transmission status
% and a collection of its signals.
%   This object is intended for an inport of the model. The model gets a non virtual
% inbound signal bus, which provides access to all received signals and to the transmission
% status of all received and sent frames. Furthermore, the sent signals could be read back
% if appropriate.
%   A Simulink.Signal object is generated for each CAN bus. The object should be attached to
% the non virtual inbound bus. The Embedded Coder is now aware of how to access the global
% C struct, which implements the CAN API.
%   Two Simulink.Bus objects are created for each frame. The object with name pattern
% *_sts_t holds the transmission status of the frame plus the other Simulink.Bus object.
% The other object contains all the signals of the frame. The signals are specified with
% name, C data type and scaling information. The latter makes the signals usable in the
% Simulink model without any ado; the Embedded Coder will take all appropriate actions to
% align the scalings of interconnected signals.
%   A Simulink.Signal object is generated for each frame. It specifies the access to the
% C struct, which collects the signals of the given frame and which is nested inside the C
% CAN bus struct.
%   The frame related Simulink.Bus object with the collection of signals and the frame
% related Simulink.Signal object are intended to implement CAN output in the Simulink
% model. (The other frame related Simulink.Bus objects are required to build up the CAN bus
% related Simulink.Bus object.) It is not possible to do this via a complete CAN bus
% related Simulink.Bus object because the Embedded Coder demands to set all signals of a
% bus; providing a value only to a sub-set is not possible. For all frames to be sent by
% the model put a bus creator (non virtual) and an outport into the model. Attach the
% Simulink.Bus object (the one without _sts in its name) to both the Simulink blocks and
% attach the Simulink.Signal object to the line interconnecting them. The signals fed into
% the bus creator will be directly written into the rights fields of the deeply nested
% global C struct, which represents the CAN bus.
%   The generated objects have names, which depend on bus and the frame's CAN ID to avoid
% ambiguities. The Simulink.Bus objects, which specify C data types, have a name ending
% with _t.
%
% This file has been generated with comFramework - codeGenerator version 1.10.0,
% see http://sourceforge.net/projects/comframe/
%
% Copyright (C) 2018 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
%
% This program is free software: you can redistribute it and/or modify it
% under the terms of the GNU Lesser General Public License as published by the
% Free Software Foundation, either version 3 of the License, or any later
% version.
%
% This program is distributed in the hope that it will be useful, but WITHOUT
% ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
% FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
% for more details.
%
% You should have received a copy of the GNU Lesser General Public License
% along with this program. If not, see <http://www.gnu.org/licenses/>.

% Create the bus elements of the Simulink Bus object, which describes the inner frame
% related struct StateEcu01 (1024, 0x400). The bus elements represent
% the signals of the frame.
tmp_busElementAry = repmat(Simulink.BusElement, 0, 1);
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'checksum';
tmp_busElementAry(end,1).DataType = 'uint8';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'speedOfRotation';
tmp_busElementAry(end,1).DataType = 'fixdt(0, 16, 0.1, 0.0)';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'sequenceCounter';
tmp_busElementAry(end,1).DataType = 'uint8';
% Create the Simulink Bus object, which describes frame
% StateEcu01 (1024, 0x400) (here without transmission status).
cap_PT_StateEcu01_1024_t = Simulink.Bus;
cap_PT_StateEcu01_1024_t.Description = ...
  ['CAN bus PT, inbound message StateEcu01 (1024,' ...
   ' 0x400)'];
cap_PT_StateEcu01_1024_t.HeaderFile = 'cap_canApi.h';
cap_PT_StateEcu01_1024_t.Elements = tmp_busElementAry;
clear tmp_busElementAry

% Create the outer frame related struct (signals plus transmission status) of frame
% StateEcu01 (1024, 0x400).
tmp_busElementAry = repmat(Simulink.BusElement, 0, 1);
tmp_busElementAry(1) = Simulink.BusElement;
tmp_busElementAry(1).Name = 'signals';
tmp_busElementAry(1).DataType = 'cap_PT_StateEcu01_1024_t';
tmp_busElementAry(2) = Simulink.BusElement;
tmp_busElementAry(2).Name = 'stsTransmission';
tmp_busElementAry(2).DataType = 'uint8';
cap_PT_StateEcu01_1024_sts_t = Simulink.Bus;
cap_PT_StateEcu01_1024_sts_t.Description = ...
  ['CAN bus PT, signals and transmission status of frame StateEcu01 (1024,' ...
   ' 0x400)'];
cap_PT_StateEcu01_1024_sts_t.HeaderFile = 'cap_canApi.h';
cap_PT_StateEcu01_1024_sts_t.Elements = tmp_busElementAry;
clear tmp_busElementAry

% Create a signal object, which can be attached to a frame based, outbound Simulink bus. An
% outport, which is configured this way will directly access the inner, frame related
% struct, that only holds the signals of the particular, inbound frame
% StateEcu01 (1024, 0x400)
PT_StateEcu01_1024 = Simulink.Signal;
PT_StateEcu01_1024.RTWInfo.StorageClass='ImportedExternPointer';
PT_StateEcu01_1024.RTWInfo.Alias='cap_pPT_StateEcu01_1024';
PT_StateEcu01_1024.Description = ...
  ['An externally initialized, constant pointer to the external struct describing the' ...
   ' inbound frame StateEcu01 (1024, 0x400).' ...
   ' Via this pointer the frame''s signals can be accessed'];


% Create the bus elements of the Simulink Bus object, which describes the inner frame
% related struct StateEcu02 (1040, 0x410). The bus elements represent
% the signals of the frame.
tmp_busElementAry = repmat(Simulink.BusElement, 0, 1);
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'checksum';
tmp_busElementAry(end,1).DataType = 'uint8';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'sequenceCounter';
tmp_busElementAry(end,1).DataType = 'uint8';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'torque';
tmp_busElementAry(end,1).DataType = 'fixdt(1, 16, 0.5, 0.0)';
% Create the Simulink Bus object, which describes frame
% StateEcu02 (1040, 0x410) (here without transmission status).
cap_PT_StateEcu02_1040_t = Simulink.Bus;
cap_PT_StateEcu02_1040_t.Description = ...
  ['CAN bus PT, inbound message StateEcu02 (1040,' ...
   ' 0x410)'];
cap_PT_StateEcu02_1040_t.HeaderFile = 'cap_canApi.h';
cap_PT_StateEcu02_1040_t.Elements = tmp_busElementAry;
clear tmp_busElementAry

% Create the outer frame related struct (signals plus transmission status) of frame
% StateEcu02 (1040, 0x410).
tmp_busElementAry = repmat(Simulink.BusElement, 0, 1);
tmp_busElementAry(1) = Simulink.BusElement;
tmp_busElementAry(1).Name = 'signals';
tmp_busElementAry(1).DataType = 'cap_PT_StateEcu02_1040_t';
tmp_busElementAry(2) = Simulink.BusElement;
tmp_busElementAry(2).Name = 'stsTransmission';
tmp_busElementAry(2).DataType = 'uint8';
cap_PT_StateEcu02_1040_sts_t = Simulink.Bus;
cap_PT_StateEcu02_1040_sts_t.Description = ...
  ['CAN bus PT, signals and transmission status of frame StateEcu02 (1040,' ...
   ' 0x410)'];
cap_PT_StateEcu02_1040_sts_t.HeaderFile = 'cap_canApi.h';
cap_PT_StateEcu02_1040_sts_t.Elements = tmp_busElementAry;
clear tmp_busElementAry

% Create a signal object, which can be attached to a frame based, outbound Simulink bus. An
% outport, which is configured this way will directly access the inner, frame related
% struct, that only holds the signals of the particular, inbound frame
% StateEcu02 (1040, 0x410)
PT_StateEcu02_1040 = Simulink.Signal;
PT_StateEcu02_1040.RTWInfo.StorageClass='ImportedExternPointer';
PT_StateEcu02_1040.RTWInfo.Alias='cap_pPT_StateEcu02_1040';
PT_StateEcu02_1040.Description = ...
  ['An externally initialized, constant pointer to the external struct describing the' ...
   ' inbound frame StateEcu02 (1040, 0x410).' ...
   ' Via this pointer the frame''s signals can be accessed'];


% Create the bus elements of the Simulink Bus object, which describes the inner frame
% related struct UserLimits (2032, 0x7f0). The bus elements represent
% the signals of the frame.
tmp_busElementAry = repmat(Simulink.BusElement, 0, 1);
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'sequenceCounter';
tmp_busElementAry(end,1).DataType = 'uint8';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'minSpeedOfRotation';
tmp_busElementAry(end,1).DataType = 'fixdt(0, 16, 1.6, 0.0)';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'maxSpeedOfRotation';
tmp_busElementAry(end,1).DataType = 'fixdt(0, 16, 1.6, 0.0)';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'checksum';
tmp_busElementAry(end,1).DataType = 'uint8';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'minPower';
tmp_busElementAry(end,1).DataType = 'fixdt(0, 16, 0.5, -10.0)';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'maxPower';
tmp_busElementAry(end,1).DataType = 'fixdt(0, 16, 0.5, -10.0)';
% Create the Simulink Bus object, which describes frame
% UserLimits (2032, 0x7f0) (here without transmission status).
cap_PT_UserLimits_2032_t = Simulink.Bus;
cap_PT_UserLimits_2032_t.Description = ...
  ['CAN bus PT, inbound message UserLimits (2032,' ...
   ' 0x7f0)'];
cap_PT_UserLimits_2032_t.HeaderFile = 'cap_canApi.h';
cap_PT_UserLimits_2032_t.Elements = tmp_busElementAry;
clear tmp_busElementAry

% Create the outer frame related struct (signals plus transmission status) of frame
% UserLimits (2032, 0x7f0).
tmp_busElementAry = repmat(Simulink.BusElement, 0, 1);
tmp_busElementAry(1) = Simulink.BusElement;
tmp_busElementAry(1).Name = 'signals';
tmp_busElementAry(1).DataType = 'cap_PT_UserLimits_2032_t';
tmp_busElementAry(2) = Simulink.BusElement;
tmp_busElementAry(2).Name = 'stsTransmission';
tmp_busElementAry(2).DataType = 'uint8';
cap_PT_UserLimits_2032_sts_t = Simulink.Bus;
cap_PT_UserLimits_2032_sts_t.Description = ...
  ['CAN bus PT, signals and transmission status of frame UserLimits (2032,' ...
   ' 0x7f0)'];
cap_PT_UserLimits_2032_sts_t.HeaderFile = 'cap_canApi.h';
cap_PT_UserLimits_2032_sts_t.Elements = tmp_busElementAry;
clear tmp_busElementAry

% Create a signal object, which can be attached to a frame based, outbound Simulink bus. An
% outport, which is configured this way will directly access the inner, frame related
% struct, that only holds the signals of the particular, inbound frame
% UserLimits (2032, 0x7f0)
PT_UserLimits_2032 = Simulink.Signal;
PT_UserLimits_2032.RTWInfo.StorageClass='ImportedExternPointer';
PT_UserLimits_2032.RTWInfo.Alias='cap_pPT_UserLimits_2032';
PT_UserLimits_2032.Description = ...
  ['An externally initialized, constant pointer to the external struct describing the' ...
   ' inbound frame UserLimits (2032, 0x7f0).' ...
   ' Via this pointer the frame''s signals can be accessed'];


% Create the bus elements of the Simulink Bus object, which describes the inner frame
% related struct InfoPowerDisplay (1536, 0x600). The bus elements represent
% the signals of the frame.
tmp_busElementAry = repmat(Simulink.BusElement, 0, 1);
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'checksum';
tmp_busElementAry(end,1).DataType = 'uint8';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'sequenceCounter';
tmp_busElementAry(end,1).DataType = 'uint8';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'power';
tmp_busElementAry(end,1).DataType = 'fixdt(0, 16, 32.0, -500000.0)';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'state';
tmp_busElementAry(end,1).DataType = 'uint8';
% Create the Simulink Bus object, which describes frame
% InfoPowerDisplay (1536, 0x600) (here without transmission status).
cap_PT_InfoPowerDisplay_1536_t = Simulink.Bus;
cap_PT_InfoPowerDisplay_1536_t.Description = ...
  ['CAN bus PT, outbound message InfoPowerDisplay (1536,' ...
   ' 0x600)'];
cap_PT_InfoPowerDisplay_1536_t.HeaderFile = 'cap_canApi.h';
cap_PT_InfoPowerDisplay_1536_t.Elements = tmp_busElementAry;
clear tmp_busElementAry

% Create the outer frame related struct (signals plus transmission status) of frame
% InfoPowerDisplay (1536, 0x600).
tmp_busElementAry = repmat(Simulink.BusElement, 0, 1);
tmp_busElementAry(1) = Simulink.BusElement;
tmp_busElementAry(1).Name = 'signals';
tmp_busElementAry(1).DataType = 'cap_PT_InfoPowerDisplay_1536_t';
tmp_busElementAry(2) = Simulink.BusElement;
tmp_busElementAry(2).Name = 'stsTransmission';
tmp_busElementAry(2).DataType = 'uint8';
cap_PT_InfoPowerDisplay_1536_sts_t = Simulink.Bus;
cap_PT_InfoPowerDisplay_1536_sts_t.Description = ...
  ['CAN bus PT, signals and transmission status of frame InfoPowerDisplay (1536,' ...
   ' 0x600)'];
cap_PT_InfoPowerDisplay_1536_sts_t.HeaderFile = 'cap_canApi.h';
cap_PT_InfoPowerDisplay_1536_sts_t.Elements = tmp_busElementAry;
clear tmp_busElementAry

% Create a signal object, which can be attached to a frame based, outbound Simulink bus. An
% outport, which is configured this way will directly access the inner, frame related
% struct, that only holds the signals of the particular, outbound frame
% InfoPowerDisplay (1536, 0x600)
PT_InfoPowerDisplay_1536 = Simulink.Signal;
PT_InfoPowerDisplay_1536.RTWInfo.StorageClass='ImportedExternPointer';
PT_InfoPowerDisplay_1536.RTWInfo.Alias='cap_pPT_InfoPowerDisplay_1536';
PT_InfoPowerDisplay_1536.Description = ...
  ['An externally initialized, constant pointer to the external struct describing the' ...
   ' outbound frame InfoPowerDisplay (1536, 0x600).' ...
   ' Via this pointer the frame''s signals can be accessed'];


% Create the bus elements of the Simulink Bus object, which describes the inner frame
% related struct StatusPowerDisplay (1537, 0x601). The bus elements represent
% the signals of the frame.
tmp_busElementAry = repmat(Simulink.BusElement, 0, 1);
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'noDlcErrors';
tmp_busElementAry(end,1).DataType = 'uint16';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'noCheckSumErrors';
tmp_busElementAry(end,1).DataType = 'uint16';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'noSqcErrors';
tmp_busElementAry(end,1).DataType = 'uint16';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'sequenceCounter';
tmp_busElementAry(end,1).DataType = 'uint8';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'checksum';
tmp_busElementAry(end,1).DataType = 'uint8';
% Create the Simulink Bus object, which describes frame
% StatusPowerDisplay (1537, 0x601) (here without transmission status).
cap_PT_StatusPowerDisplay_1537_t = Simulink.Bus;
cap_PT_StatusPowerDisplay_1537_t.Description = ...
  ['CAN bus PT, outbound message StatusPowerDisplay (1537,' ...
   ' 0x601)'];
cap_PT_StatusPowerDisplay_1537_t.HeaderFile = 'cap_canApi.h';
cap_PT_StatusPowerDisplay_1537_t.Elements = tmp_busElementAry;
clear tmp_busElementAry

% Create the outer frame related struct (signals plus transmission status) of frame
% StatusPowerDisplay (1537, 0x601).
tmp_busElementAry = repmat(Simulink.BusElement, 0, 1);
tmp_busElementAry(1) = Simulink.BusElement;
tmp_busElementAry(1).Name = 'signals';
tmp_busElementAry(1).DataType = 'cap_PT_StatusPowerDisplay_1537_t';
tmp_busElementAry(2) = Simulink.BusElement;
tmp_busElementAry(2).Name = 'stsTransmission';
tmp_busElementAry(2).DataType = 'uint8';
cap_PT_StatusPowerDisplay_1537_sts_t = Simulink.Bus;
cap_PT_StatusPowerDisplay_1537_sts_t.Description = ...
  ['CAN bus PT, signals and transmission status of frame StatusPowerDisplay (1537,' ...
   ' 0x601)'];
cap_PT_StatusPowerDisplay_1537_sts_t.HeaderFile = 'cap_canApi.h';
cap_PT_StatusPowerDisplay_1537_sts_t.Elements = tmp_busElementAry;
clear tmp_busElementAry

% Create a signal object, which can be attached to a frame based, outbound Simulink bus. An
% outport, which is configured this way will directly access the inner, frame related
% struct, that only holds the signals of the particular, outbound frame
% StatusPowerDisplay (1537, 0x601)
PT_StatusPowerDisplay_1537 = Simulink.Signal;
PT_StatusPowerDisplay_1537.RTWInfo.StorageClass='ImportedExternPointer';
PT_StatusPowerDisplay_1537.RTWInfo.Alias='cap_pPT_StatusPowerDisplay_1537';
PT_StatusPowerDisplay_1537.Description = ...
  ['An externally initialized, constant pointer to the external struct describing the' ...
   ' outbound frame StatusPowerDisplay (1537, 0x601).' ...
   ' Via this pointer the frame''s signals can be accessed'];


% Create the bus elements of the Simulink Bus object, which describes the inner frame
% related struct LimitsPowerDisplay (1538, 0x602). The bus elements represent
% the signals of the frame.
tmp_busElementAry = repmat(Simulink.BusElement, 0, 1);
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'sequenceCounter';
tmp_busElementAry(end,1).DataType = 'uint8';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'belowMinSpeedOfRotation';
tmp_busElementAry(end,1).DataType = 'boolean';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'aboveMaxSpeedOfRotation';
tmp_busElementAry(end,1).DataType = 'boolean';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'belowMinPower';
tmp_busElementAry(end,1).DataType = 'boolean';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'aboveMaxPower';
tmp_busElementAry(end,1).DataType = 'boolean';
% Create the Simulink Bus object, which describes frame
% LimitsPowerDisplay (1538, 0x602) (here without transmission status).
cap_PT_LimitsPowerDisplay_1538_t = Simulink.Bus;
cap_PT_LimitsPowerDisplay_1538_t.Description = ...
  ['CAN bus PT, outbound message LimitsPowerDisplay (1538,' ...
   ' 0x602)'];
cap_PT_LimitsPowerDisplay_1538_t.HeaderFile = 'cap_canApi.h';
cap_PT_LimitsPowerDisplay_1538_t.Elements = tmp_busElementAry;
clear tmp_busElementAry

% Create the outer frame related struct (signals plus transmission status) of frame
% LimitsPowerDisplay (1538, 0x602).
tmp_busElementAry = repmat(Simulink.BusElement, 0, 1);
tmp_busElementAry(1) = Simulink.BusElement;
tmp_busElementAry(1).Name = 'signals';
tmp_busElementAry(1).DataType = 'cap_PT_LimitsPowerDisplay_1538_t';
tmp_busElementAry(2) = Simulink.BusElement;
tmp_busElementAry(2).Name = 'stsTransmission';
tmp_busElementAry(2).DataType = 'uint8';
cap_PT_LimitsPowerDisplay_1538_sts_t = Simulink.Bus;
cap_PT_LimitsPowerDisplay_1538_sts_t.Description = ...
  ['CAN bus PT, signals and transmission status of frame LimitsPowerDisplay (1538,' ...
   ' 0x602)'];
cap_PT_LimitsPowerDisplay_1538_sts_t.HeaderFile = 'cap_canApi.h';
cap_PT_LimitsPowerDisplay_1538_sts_t.Elements = tmp_busElementAry;
clear tmp_busElementAry

% Create a signal object, which can be attached to a frame based, outbound Simulink bus. An
% outport, which is configured this way will directly access the inner, frame related
% struct, that only holds the signals of the particular, outbound frame
% LimitsPowerDisplay (1538, 0x602)
PT_LimitsPowerDisplay_1538 = Simulink.Signal;
PT_LimitsPowerDisplay_1538.RTWInfo.StorageClass='ImportedExternPointer';
PT_LimitsPowerDisplay_1538.RTWInfo.Alias='cap_pPT_LimitsPowerDisplay_1538';
PT_LimitsPowerDisplay_1538.Description = ...
  ['An externally initialized, constant pointer to the external struct describing the' ...
   ' outbound frame LimitsPowerDisplay (1538, 0x602).' ...
   ' Via this pointer the frame''s signals can be accessed'];



% Once we have the array of all frame related bus objects of this bus we can assemble the
% array of bus elements for the CAN bus related Bus object.
tmp_busElementAry = repmat(Simulink.BusElement, 0, 1);
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'PT_StateEcu01_1024_sts';
tmp_busElementAry(end,1).DataType = 'cap_PT_StateEcu01_1024_sts_t';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'PT_StateEcu02_1040_sts';
tmp_busElementAry(end,1).DataType = 'cap_PT_StateEcu02_1040_sts_t';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'PT_UserLimits_2032_sts';
tmp_busElementAry(end,1).DataType = 'cap_PT_UserLimits_2032_sts_t';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'PT_InfoPowerDisplay_1536_sts';
tmp_busElementAry(end,1).DataType = 'cap_PT_InfoPowerDisplay_1536_sts_t';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'PT_StatusPowerDisplay_1537_sts';
tmp_busElementAry(end,1).DataType = 'cap_PT_StatusPowerDisplay_1537_sts_t';
tmp_busElementAry(end+1,1) = Simulink.BusElement;
tmp_busElementAry(end,1).Name = 'PT_LimitsPowerDisplay_1538_sts';
tmp_busElementAry(end,1).DataType = 'cap_PT_LimitsPowerDisplay_1538_sts_t';

% Once we have the array of frame related bus elements we can assemble the bus object for
% the complete CAN bus PT.
cap_canBus_PT_t = Simulink.Bus;
cap_canBus_PT_t.Description = 'CAN bus PT';
cap_canBus_PT_t.HeaderFile = 'cap_canApi.h';
cap_canBus_PT_t.Elements = tmp_busElementAry;
clear tmp_busElementAry


% Create a signal object, which can be attached to the CAN bus PT related, inbound,
% nonvirtual Simulink bus. An inport, which is configured this way can be connected to a
% Simulink bus selector block. Any field from the nested struct can be selected and direct
% access code will be generated.
canBus_PT = Simulink.Signal;
canBus_PT.RTWInfo.StorageClass='ImportedExtern';
canBus_PT.RTWInfo.Alias='cap_canBus_PT';
canBus_PT.Description = ...
  ['The externally initialized nested struct, which specifies all elements of CAN bus PT'];