/** The instruction stream of compiled regular expression reHttpHdrTime. The regular
    expression is:\n
    "^HTTP/1.1 <\d+> <[a-zA-Z 0-9]+>\N+Content-Length: \d+\N+Content-Type: (application/json|text/html); charset=<[a-zA-Z0-8-]+>\N+Date: <<\A{3}>, <\d{2}> <\A{3}> <\d{4}> <<\d{2}>:<\d{2}>:<\d{2}>>> GMT(\N+[^{]*\{(.|\N)*?\x22currentDateTime\x22:\x22<\d{4}>-<\d{2}>-<\d{2}>.<\d{2}>:<\d{2}>)?" */
static const uint8_t ats_reHttpHdrTime_iStream[529] =
{
    /* 0000 */  I_CARET,
    /* 0001 */  I_LIT('H'),
    /* 0002 */  I_LIT('T'),
    /* 0003 */  I_LIT('T'),
    /* 0004 */  I_LIT('P'),
    /* 0005 */  I_LIT('/'),
    /* 0006 */  I_LIT('1'),
    /* 0007 */  I_ANY,
    /* 0008 */  I_LIT('1'),
    /* 0009 */  I_LIT(' '),
    /* 0010 */  I_CAP(0),
    /* 0012 */  I_LOOP(1, 1, 1, 255),	// -> 19
    /* 0018 */  I_DIGIT,
    /* 0019 */  I_LOOPEND(1),	// <- 12
    /* 0022 */  I_CAPEND(0),
    /* 0024 */  I_LIT(' '),
    /* 0025 */  I_CAP(1),
    /* 0027 */  I_LOOP(2, 3, 1, 255),	// -> 36
    /* 0033 */  I_CHARSET(397),	// -> 433
    /* 0036 */  I_LOOPEND(3),	// <- 27
    /* 0039 */  I_CAPEND(1),
    /* 0041 */  I_LOOP(3, 1, 1, 255),	// -> 48
    /* 0047 */  I_CRLF,
    /* 0048 */  I_LOOPEND(1),	// <- 41
    /* 0051 */  I_LIT('C'),
    /* 0052 */  I_LIT('o'),
    /* 0053 */  I_LIT('n'),
    /* 0054 */  I_LIT('t'),
    /* 0055 */  I_LIT('e'),
    /* 0056 */  I_LIT('n'),
    /* 0057 */  I_LIT('t'),
    /* 0058 */  I_LIT('-'),
    /* 0059 */  I_LIT('L'),
    /* 0060 */  I_LIT('e'),
    /* 0061 */  I_LIT('n'),
    /* 0062 */  I_LIT('g'),
    /* 0063 */  I_LIT('t'),
    /* 0064 */  I_LIT('h'),
    /* 0065 */  I_LIT(':'),
    /* 0066 */  I_LIT(' '),
    /* 0067 */  I_LOOP(4, 1, 1, 255),	// -> 74
    /* 0073 */  I_DIGIT,
    /* 0074 */  I_LOOPEND(1),	// <- 67
    /* 0077 */  I_LOOP(5, 1, 1, 255),	// -> 84
    /* 0083 */  I_CRLF,
    /* 0084 */  I_LOOPEND(1),	// <- 77
    /* 0087 */  I_LIT('C'),
    /* 0088 */  I_LIT('o'),
    /* 0089 */  I_LIT('n'),
    /* 0090 */  I_LIT('t'),
    /* 0091 */  I_LIT('e'),
    /* 0092 */  I_LIT('n'),
    /* 0093 */  I_LIT('t'),
    /* 0094 */  I_LIT('-'),
    /* 0095 */  I_LIT('T'),
    /* 0096 */  I_LIT('y'),
    /* 0097 */  I_LIT('p'),
    /* 0098 */  I_LIT('e'),
    /* 0099 */  I_LIT(':'),
    /* 0100 */  I_LIT(' '),
    /* 0101 */  I_OR(19),	// -> 123
    /* 0104 */  I_LIT('a'),
    /* 0105 */  I_LIT('p'),
    /* 0106 */  I_LIT('p'),
    /* 0107 */  I_LIT('l'),
    /* 0108 */  I_LIT('i'),
    /* 0109 */  I_LIT('c'),
    /* 0110 */  I_LIT('a'),
    /* 0111 */  I_LIT('t'),
    /* 0112 */  I_LIT('i'),
    /* 0113 */  I_LIT('o'),
    /* 0114 */  I_LIT('n'),
    /* 0115 */  I_LIT('/'),
    /* 0116 */  I_LIT('j'),
    /* 0117 */  I_LIT('s'),
    /* 0118 */  I_LIT('o'),
    /* 0119 */  I_LIT('n'),
    /* 0120 */  I_JMP(9),	// -> 132
    /* 0123 */  I_LIT('t'),
    /* 0124 */  I_LIT('e'),
    /* 0125 */  I_LIT('x'),
    /* 0126 */  I_LIT('t'),
    /* 0127 */  I_LIT('/'),
    /* 0128 */  I_LIT('h'),
    /* 0129 */  I_LIT('t'),
    /* 0130 */  I_LIT('m'),
    /* 0131 */  I_LIT('l'),
    /* 0132 */  I_LIT(';'),
    /* 0133 */  I_LIT(' '),
    /* 0134 */  I_LIT('c'),
    /* 0135 */  I_LIT('h'),
    /* 0136 */  I_LIT('a'),
    /* 0137 */  I_LIT('r'),
    /* 0138 */  I_LIT('s'),
    /* 0139 */  I_LIT('e'),
    /* 0140 */  I_LIT('t'),
    /* 0141 */  I_LIT('='),
    /* 0142 */  I_CAP(2),
    /* 0144 */  I_LOOP(6, 3, 1, 255),	// -> 153
    /* 0150 */  I_CHARSET(312),	// -> 465
    /* 0153 */  I_LOOPEND(3),	// <- 144
    /* 0156 */  I_CAPEND(2),
    /* 0158 */  I_LOOP(7, 1, 1, 255),	// -> 165
    /* 0164 */  I_CRLF,
    /* 0165 */  I_LOOPEND(1),	// <- 158
    /* 0168 */  I_LIT('D'),
    /* 0169 */  I_LIT('a'),
    /* 0170 */  I_LIT('t'),
    /* 0171 */  I_LIT('e'),
    /* 0172 */  I_LIT(':'),
    /* 0173 */  I_LIT(' '),
    /* 0174 */  I_CAP(3),
    /* 0176 */  I_CAP(4),
    /* 0178 */  I_LOOP(8, 1, 3, 3),	// -> 185
    /* 0184 */  I_LTR,
    /* 0185 */  I_LOOPEND(1),	// <- 178
    /* 0188 */  I_CAPEND(4),
    /* 0190 */  I_LIT(','),
    /* 0191 */  I_LIT(' '),
    /* 0192 */  I_CAP(5),
    /* 0194 */  I_LOOP(9, 1, 2, 2),	// -> 201
    /* 0200 */  I_DIGIT,
    /* 0201 */  I_LOOPEND(1),	// <- 194
    /* 0204 */  I_CAPEND(5),
    /* 0206 */  I_LIT(' '),
    /* 0207 */  I_CAP(6),
    /* 0209 */  I_LOOP(10, 1, 3, 3),	// -> 216
    /* 0215 */  I_LTR,
    /* 0216 */  I_LOOPEND(1),	// <- 209
    /* 0219 */  I_CAPEND(6),
    /* 0221 */  I_LIT(' '),
    /* 0222 */  I_CAP(7),
    /* 0224 */  I_LOOP(11, 1, 4, 4),	// -> 231
    /* 0230 */  I_DIGIT,
    /* 0231 */  I_LOOPEND(1),	// <- 224
    /* 0234 */  I_CAPEND(7),
    /* 0236 */  I_LIT(' '),
    /* 0237 */  I_CAP(8),
    /* 0239 */  I_CAP(9),
    /* 0241 */  I_LOOP(12, 1, 2, 2),	// -> 248
    /* 0247 */  I_DIGIT,
    /* 0248 */  I_LOOPEND(1),	// <- 241
    /* 0251 */  I_CAPEND(9),
    /* 0253 */  I_LIT(':'),
    /* 0254 */  I_CAP(10),
    /* 0256 */  I_LOOP(13, 1, 2, 2),	// -> 263
    /* 0262 */  I_DIGIT,
    /* 0263 */  I_LOOPEND(1),	// <- 256
    /* 0266 */  I_CAPEND(10),
    /* 0268 */  I_LIT(':'),
    /* 0269 */  I_CAP(11),
    /* 0271 */  I_LOOP(14, 1, 2, 2),	// -> 278
    /* 0277 */  I_DIGIT,
    /* 0278 */  I_LOOPEND(1),	// <- 271
    /* 0281 */  I_CAPEND(11),
    /* 0283 */  I_CAPEND(8),
    /* 0285 */  I_CAPEND(3),
    /* 0287 */  I_LIT(' '),
    /* 0288 */  I_LIT('G'),
    /* 0289 */  I_LIT('M'),
    /* 0290 */  I_LIT('T'),
    /* 0291 */  I_LOOP(23, 133, 0, 1),	// -> 430
    /* 0297 */  I_LOOP(15, 1, 1, 255),	// -> 304
    /* 0303 */  I_CRLF,
    /* 0304 */  I_LOOPEND(1),	// <- 297
    /* 0307 */  I_LOOP(16, 3, 0, 255),	// -> 316
    /* 0313 */  I_CHARSET(181),	// -> 497
    /* 0316 */  I_LOOPEND(3),	// <- 307
    /* 0319 */  I_LIT('{'),
    /* 0320 */  I_LOOP_NG(17, 8, 0, 255),	// -> 334
    /* 0326 */  I_OR(4),	// -> 333
    /* 0329 */  I_ANY,
    /* 0330 */  I_JMP(1),	// -> 334
    /* 0333 */  I_CRLF,
    /* 0334 */  I_LOOPEND(8),	// <- 320
    /* 0337 */  I_LIT('"'),
    /* 0338 */  I_LIT('c'),
    /* 0339 */  I_LIT('u'),
    /* 0340 */  I_LIT('r'),
    /* 0341 */  I_LIT('r'),
    /* 0342 */  I_LIT('e'),
    /* 0343 */  I_LIT('n'),
    /* 0344 */  I_LIT('t'),
    /* 0345 */  I_LIT('D'),
    /* 0346 */  I_LIT('a'),
    /* 0347 */  I_LIT('t'),
    /* 0348 */  I_LIT('e'),
    /* 0349 */  I_LIT('T'),
    /* 0350 */  I_LIT('i'),
    /* 0351 */  I_LIT('m'),
    /* 0352 */  I_LIT('e'),
    /* 0353 */  I_LIT('"'),
    /* 0354 */  I_LIT(':'),
    /* 0355 */  I_LIT('"'),
    /* 0356 */  I_CAP(12),
    /* 0358 */  I_LOOP(18, 1, 4, 4),	// -> 365
    /* 0364 */  I_DIGIT,
    /* 0365 */  I_LOOPEND(1),	// <- 358
    /* 0368 */  I_CAPEND(12),
    /* 0370 */  I_LIT('-'),
    /* 0371 */  I_CAP(13),
    /* 0373 */  I_LOOP(19, 1, 2, 2),	// -> 380
    /* 0379 */  I_DIGIT,
    /* 0380 */  I_LOOPEND(1),	// <- 373
    /* 0383 */  I_CAPEND(13),
    /* 0385 */  I_LIT('-'),
    /* 0386 */  I_CAP(14),
    /* 0388 */  I_LOOP(20, 1, 2, 2),	// -> 395
    /* 0394 */  I_DIGIT,
    /* 0395 */  I_LOOPEND(1),	// <- 388
    /* 0398 */  I_CAPEND(14),
    /* 0400 */  I_ANY,
    /* 0401 */  I_CAP(15),
    /* 0403 */  I_LOOP(21, 1, 2, 2),	// -> 410
    /* 0409 */  I_DIGIT,
    /* 0410 */  I_LOOPEND(1),	// <- 403
    /* 0413 */  I_CAPEND(15),
    /* 0415 */  I_LIT(':'),
    /* 0416 */  I_CAP(16),
    /* 0418 */  I_LOOP(22, 1, 2, 2),	// -> 425
    /* 0424 */  I_DIGIT,
    /* 0425 */  I_LOOPEND(1),	// <- 418
    /* 0428 */  I_CAPEND(16),
    /* 0430 */  I_LOOPEND(133),	// <- 291
    /* 0433 */  I_DC(0x00, 0x00, 0x00, 0x00),
    /* 0437 */  I_DC(0x01, 0x00, 0xFF, 0x03),
    /* 0441 */  I_DC(0xFE, 0xFF, 0xFF, 0x07),
    /* 0445 */  I_DC(0xFE, 0xFF, 0xFF, 0x07),
    /* 0449 */  I_DC(0x00, 0x00, 0x00, 0x00),
    /* 0453 */  I_DC(0x00, 0x00, 0x00, 0x00),
    /* 0457 */  I_DC(0x00, 0x00, 0x00, 0x00),
    /* 0461 */  I_DC(0x00, 0x00, 0x00, 0x00),
    /* 0465 */  I_DC(0x00, 0x00, 0x00, 0x00),
    /* 0469 */  I_DC(0x00, 0x20, 0xFF, 0x01),
    /* 0473 */  I_DC(0xFE, 0xFF, 0xFF, 0x07),
    /* 0477 */  I_DC(0xFE, 0xFF, 0xFF, 0x07),
    /* 0481 */  I_DC(0x00, 0x00, 0x00, 0x00),
    /* 0485 */  I_DC(0x00, 0x00, 0x00, 0x00),
    /* 0489 */  I_DC(0x00, 0x00, 0x00, 0x00),
    /* 0493 */  I_DC(0x00, 0x00, 0x00, 0x00),
    /* 0497 */  I_DC(0xFF, 0xFF, 0xFF, 0xFF),
    /* 0501 */  I_DC(0xFF, 0xFF, 0xFF, 0xFF),
    /* 0505 */  I_DC(0xFF, 0xFF, 0xFF, 0xFF),
    /* 0509 */  I_DC(0xFF, 0xFF, 0xFF, 0xF7),
    /* 0513 */  I_DC(0xFF, 0xFF, 0xFF, 0xFF),
    /* 0517 */  I_DC(0xFF, 0xFF, 0xFF, 0xFF),
    /* 0521 */  I_DC(0xFF, 0xFF, 0xFF, 0xFF),
    /* 0525 */  I_DC(0xFF, 0xFF, 0xFF, 0xFF),
};

/** The compiled regular expression reHttpHdrTime:\n
    "^HTTP/1.1 <\d+> <[a-zA-Z 0-9]+>\N+Content-Length: \d+\N+Content-Type: (application/json|text/html); charset=<[a-zA-Z0-8-]+>\N+Date: <<\A{3}>, <\d{2}> <\A{3}> <\d{4}> <<\d{2}>:<\d{2}>:<\d{2}>>> GMT(\N+[^{]*\{(.|\N)*?\x22currentDateTime\x22:\x22<\d{4}>-<\d{2}>-<\d{2}>.<\d{2}>:<\d{2}>)?" */
static const struct re_compiledRegExp_t ats_reHttpHdrTime =
{
    .iStream       = (uint8_t*)&ats_reHttpHdrTime_iStream[0],
    .lenIStream    = 433u,
    .noCaptureGrps = 17u,
    .noCharSets    = 3u,
};


