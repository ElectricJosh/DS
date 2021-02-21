
C:/Users/joshb/Desktop/NewCypressCode/1_Blank/EmptyWicedBluetooth_mainapp/Debug/EmptyWicedBluetooth_mainapp.elf:     file format elf32-littlearm


Disassembly of section .app_xip_area:

00511500 <app_gatt_callback>:
  511500:	b570      	push	{r4, r5, r6, lr}
  511502:	460d      	mov	r5, r1
  511504:	2100      	movs	r1, #0
  511506:	4606      	mov	r6, r0
  511508:	4a1d      	ldr	r2, [pc, #116]	; (511580 <app_gatt_callback+0x80>)
  51150a:	4c1e      	ldr	r4, [pc, #120]	; (511584 <app_gatt_callback+0x84>)
  51150c:	4608      	mov	r0, r1
  51150e:	47a0      	blx	r4
  511510:	b11e      	cbz	r6, 51151a <app_gatt_callback+0x1a>
  511512:	2e04      	cmp	r6, #4
  511514:	d006      	beq.n	511524 <app_gatt_callback+0x24>
  511516:	4a1c      	ldr	r2, [pc, #112]	; (511588 <app_gatt_callback+0x88>)
  511518:	e000      	b.n	51151c <app_gatt_callback+0x1c>
  51151a:	4a1c      	ldr	r2, [pc, #112]	; (51158c <app_gatt_callback+0x8c>)
  51151c:	2100      	movs	r1, #0
  51151e:	4608      	mov	r0, r1
  511520:	47a0      	blx	r4
  511522:	e026      	b.n	511572 <app_gatt_callback+0x72>
  511524:	2100      	movs	r1, #0
  511526:	4a1a      	ldr	r2, [pc, #104]	; (511590 <app_gatt_callback+0x90>)
  511528:	4608      	mov	r0, r1
  51152a:	47a0      	blx	r4
  51152c:	78ab      	ldrb	r3, [r5, #2]
  51152e:	2b02      	cmp	r3, #2
  511530:	d021      	beq.n	511576 <app_gatt_callback+0x76>
  511532:	2b06      	cmp	r3, #6
  511534:	d021      	beq.n	51157a <app_gatt_callback+0x7a>
  511536:	2b01      	cmp	r3, #1
  511538:	d11b      	bne.n	511572 <app_gatt_callback+0x72>
  51153a:	2100      	movs	r1, #0
  51153c:	4a15      	ldr	r2, [pc, #84]	; (511594 <app_gatt_callback+0x94>)
  51153e:	4608      	mov	r0, r1
  511540:	47a0      	blx	r4
  511542:	2100      	movs	r1, #0
  511544:	88ab      	ldrh	r3, [r5, #4]
  511546:	4a14      	ldr	r2, [pc, #80]	; (511598 <app_gatt_callback+0x98>)
  511548:	4608      	mov	r0, r1
  51154a:	47a0      	blx	r4
  51154c:	88ab      	ldrh	r3, [r5, #4]
  51154e:	2b09      	cmp	r3, #9
  511550:	d10f      	bne.n	511572 <app_gatt_callback+0x72>
  511552:	2100      	movs	r1, #0
  511554:	4a11      	ldr	r2, [pc, #68]	; (51159c <app_gatt_callback+0x9c>)
  511556:	4608      	mov	r0, r1
  511558:	47a0      	blx	r4
  51155a:	4a11      	ldr	r2, [pc, #68]	; (5115a0 <app_gatt_callback+0xa0>)
  51155c:	4b11      	ldr	r3, [pc, #68]	; (5115a4 <app_gatt_callback+0xa4>)
  51155e:	8812      	ldrh	r2, [r2, #0]
  511560:	88e8      	ldrh	r0, [r5, #6]
  511562:	4d11      	ldr	r5, [pc, #68]	; (5115a8 <app_gatt_callback+0xa8>)
  511564:	2108      	movs	r1, #8
  511566:	47a8      	blx	r5
  511568:	2100      	movs	r1, #0
  51156a:	4603      	mov	r3, r0
  51156c:	4a0f      	ldr	r2, [pc, #60]	; (5115ac <app_gatt_callback+0xac>)
  51156e:	4608      	mov	r0, r1
  511570:	47a0      	blx	r4
  511572:	2000      	movs	r0, #0
  511574:	bd70      	pop	{r4, r5, r6, pc}
  511576:	4a0e      	ldr	r2, [pc, #56]	; (5115b0 <app_gatt_callback+0xb0>)
  511578:	e7d0      	b.n	51151c <app_gatt_callback+0x1c>
  51157a:	4a0e      	ldr	r2, [pc, #56]	; (5115b4 <app_gatt_callback+0xb4>)
  51157c:	e7ce      	b.n	51151c <app_gatt_callback+0x1c>
  51157e:	bf00      	nop
  511580:	005116cc 	.word	0x005116cc
  511584:	000d3259 	.word	0x000d3259
  511588:	00511774 	.word	0x00511774
  51158c:	005116dc 	.word	0x005116dc
  511590:	005116f4 	.word	0x005116f4
  511594:	00511713 	.word	0x00511713
  511598:	00511720 	.word	0x00511720
  51159c:	0051172d 	.word	0x0051172d
  5115a0:	0051188c 	.word	0x0051188c
  5115a4:	0020fb0e 	.word	0x0020fb0e
  5115a8:	000d2993 	.word	0x000d2993
  5115ac:	00511743 	.word	0x00511743
  5115b0:	00511756 	.word	0x00511756
  5115b4:	00511764 	.word	0x00511764

005115b8 <application_start>:
  5115b8:	b510      	push	{r4, lr}
  5115ba:	2004      	movs	r0, #4
  5115bc:	4b06      	ldr	r3, [pc, #24]	; (5115d8 <application_start+0x20>)
  5115be:	4798      	blx	r3
  5115c0:	2100      	movs	r1, #0
  5115c2:	4a06      	ldr	r2, [pc, #24]	; (5115dc <application_start+0x24>)
  5115c4:	4b06      	ldr	r3, [pc, #24]	; (5115e0 <application_start+0x28>)
  5115c6:	4608      	mov	r0, r1
  5115c8:	4798      	blx	r3
  5115ca:	4a06      	ldr	r2, [pc, #24]	; (5115e4 <application_start+0x2c>)
  5115cc:	4906      	ldr	r1, [pc, #24]	; (5115e8 <application_start+0x30>)
  5115ce:	4807      	ldr	r0, [pc, #28]	; (5115ec <application_start+0x34>)
  5115d0:	4b07      	ldr	r3, [pc, #28]	; (5115f0 <application_start+0x38>)
  5115d2:	e8bd 4010 	ldmia.w	sp!, {r4, lr}
  5115d6:	4718      	bx	r3
  5115d8:	000d2dc5 	.word	0x000d2dc5
  5115dc:	00511789 	.word	0x00511789
  5115e0:	000d3259 	.word	0x000d3259
  5115e4:	005117fc 	.word	0x005117fc
  5115e8:	0051180c 	.word	0x0051180c
  5115ec:	0051163d 	.word	0x0051163d
  5115f0:	0003f17f 	.word	0x0003f17f

005115f4 <app_set_advertisement_data>:
  5115f4:	b510      	push	{r4, lr}
  5115f6:	b088      	sub	sp, #32
  5115f8:	2306      	movs	r3, #6
  5115fa:	f88d 3007 	strb.w	r3, [sp, #7]
  5115fe:	2301      	movs	r3, #1
  511600:	f88d 300e 	strb.w	r3, [sp, #14]
  511604:	f8ad 300c 	strh.w	r3, [sp, #12]
  511608:	f10d 0307 	add.w	r3, sp, #7
  51160c:	9302      	str	r3, [sp, #8]
  51160e:	2309      	movs	r3, #9
  511610:	f88d 3016 	strb.w	r3, [sp, #22]
  511614:	4b06      	ldr	r3, [pc, #24]	; (511630 <app_set_advertisement_data+0x3c>)
  511616:	681c      	ldr	r4, [r3, #0]
  511618:	4b06      	ldr	r3, [pc, #24]	; (511634 <app_set_advertisement_data+0x40>)
  51161a:	4620      	mov	r0, r4
  51161c:	4798      	blx	r3
  51161e:	9404      	str	r4, [sp, #16]
  511620:	f8ad 0014 	strh.w	r0, [sp, #20]
  511624:	a902      	add	r1, sp, #8
  511626:	4b04      	ldr	r3, [pc, #16]	; (511638 <app_set_advertisement_data+0x44>)
  511628:	2002      	movs	r0, #2
  51162a:	4798      	blx	r3
  51162c:	b008      	add	sp, #32
  51162e:	bd10      	pop	{r4, pc}
  511630:	0051180c 	.word	0x0051180c
  511634:	00055ad3 	.word	0x00055ad3
  511638:	0008a19d 	.word	0x0008a19d

0051163c <app_bt_management_callback>:
  51163c:	2816      	cmp	r0, #22
  51163e:	b537      	push	{r0, r1, r2, r4, r5, lr}
  511640:	4604      	mov	r4, r0
  511642:	d821      	bhi.n	511688 <app_bt_management_callback+0x4c>
  511644:	2301      	movs	r3, #1
  511646:	4a14      	ldr	r2, [pc, #80]	; (511698 <app_bt_management_callback+0x5c>)
  511648:	4083      	lsls	r3, r0
  51164a:	4213      	tst	r3, r2
  51164c:	d119      	bne.n	511682 <app_bt_management_callback+0x46>
  51164e:	b9d8      	cbnz	r0, 511688 <app_bt_management_callback+0x4c>
  511650:	8809      	ldrh	r1, [r1, #0]
  511652:	4a12      	ldr	r2, [pc, #72]	; (51169c <app_bt_management_callback+0x60>)
  511654:	4b12      	ldr	r3, [pc, #72]	; (5116a0 <app_bt_management_callback+0x64>)
  511656:	4d13      	ldr	r5, [pc, #76]	; (5116a4 <app_bt_management_callback+0x68>)
  511658:	2900      	cmp	r1, #0
  51165a:	bf18      	it	ne
  51165c:	4613      	movne	r3, r2
  51165e:	4a12      	ldr	r2, [pc, #72]	; (5116a8 <app_bt_management_callback+0x6c>)
  511660:	4601      	mov	r1, r0
  511662:	47a8      	blx	r5
  511664:	4b11      	ldr	r3, [pc, #68]	; (5116ac <app_bt_management_callback+0x70>)
  511666:	4812      	ldr	r0, [pc, #72]	; (5116b0 <app_bt_management_callback+0x74>)
  511668:	4798      	blx	r3
  51166a:	4b12      	ldr	r3, [pc, #72]	; (5116b4 <app_bt_management_callback+0x78>)
  51166c:	4812      	ldr	r0, [pc, #72]	; (5116b8 <app_bt_management_callback+0x7c>)
  51166e:	8819      	ldrh	r1, [r3, #0]
  511670:	4b12      	ldr	r3, [pc, #72]	; (5116bc <app_bt_management_callback+0x80>)
  511672:	4798      	blx	r3
  511674:	4b12      	ldr	r3, [pc, #72]	; (5116c0 <app_bt_management_callback+0x84>)
  511676:	4798      	blx	r3
  511678:	4622      	mov	r2, r4
  51167a:	4621      	mov	r1, r4
  51167c:	2003      	movs	r0, #3
  51167e:	4b11      	ldr	r3, [pc, #68]	; (5116c4 <app_bt_management_callback+0x88>)
  511680:	4798      	blx	r3
  511682:	2000      	movs	r0, #0
  511684:	b003      	add	sp, #12
  511686:	bd30      	pop	{r4, r5, pc}
  511688:	2100      	movs	r1, #0
  51168a:	9400      	str	r4, [sp, #0]
  51168c:	4623      	mov	r3, r4
  51168e:	4a0e      	ldr	r2, [pc, #56]	; (5116c8 <app_bt_management_callback+0x8c>)
  511690:	4c04      	ldr	r4, [pc, #16]	; (5116a4 <app_bt_management_callback+0x68>)
  511692:	4608      	mov	r0, r1
  511694:	47a0      	blx	r4
  511696:	e7f4      	b.n	511682 <app_bt_management_callback+0x46>
  511698:	007c3c00 	.word	0x007c3c00
  51169c:	005117a8 	.word	0x005117a8
  5116a0:	005117a0 	.word	0x005117a0
  5116a4:	000d3259 	.word	0x000d3259
  5116a8:	005117b0 	.word	0x005117b0
  5116ac:	0008308f 	.word	0x0008308f
  5116b0:	00511501 	.word	0x00511501
  5116b4:	00511894 	.word	0x00511894
  5116b8:	00511896 	.word	0x00511896
  5116bc:	000d29c3 	.word	0x000d29c3
  5116c0:	005115f5 	.word	0x005115f5
  5116c4:	0008a13d 	.word	0x0008a13d
  5116c8:	005117c8 	.word	0x005117c8
  5116cc:	54544147 	.word	0x54544147
  5116d0:	6c616320 	.word	0x6c616320
  5116d4:	6361626c 	.word	0x6361626c
  5116d8:	000a0d6b 	.word	0x000a0d6b
  5116dc:	54544147 	.word	0x54544147
  5116e0:	6e6f4320 	.word	0x6e6f4320
  5116e4:	7463656e 	.word	0x7463656e
  5116e8:	206e6f69 	.word	0x206e6f69
  5116ec:	6e657645 	.word	0x6e657645
  5116f0:	000a0d74 	.word	0x000a0d74
  5116f4:	54544147 	.word	0x54544147
  5116f8:	74744120 	.word	0x74744120
  5116fc:	75626972 	.word	0x75626972
  511700:	52206574 	.word	0x52206574
  511704:	65757165 	.word	0x65757165
  511708:	45207473 	.word	0x45207473
  51170c:	746e6576 	.word	0x746e6576
  511710:	52000a0d 	.word	0x52000a0d
  511714:	20646165 	.word	0x20646165
  511718:	6e657645 	.word	0x6e657645
  51171c:	000a0d74 	.word	0x000a0d74
  511720:	646e6148 	.word	0x646e6148
  511724:	2520656c 	.word	0x2520656c
  511728:	0a0d2064 	.word	0x0a0d2064
  51172c:	61655200 	.word	0x61655200
  511730:	65522064 	.word	0x65522064
  511734:	73657571 	.word	0x73657571
  511738:	65522074 	.word	0x65522074
  51173c:	76696563 	.word	0x76696563
  511740:	47006465 	.word	0x47006465
  511744:	20545441 	.word	0x20545441
  511748:	74617473 	.word	0x74617473
  51174c:	203a7375 	.word	0x203a7375
  511750:	0d206425 	.word	0x0d206425
  511754:	7257000a 	.word	0x7257000a
  511758:	20657469 	.word	0x20657469
  51175c:	6e657645 	.word	0x6e657645
  511760:	000a0d74 	.word	0x000a0d74
  511764:	666e6f43 	.word	0x666e6f43
  511768:	206d7269 	.word	0x206d7269
  51176c:	6e657645 	.word	0x6e657645
  511770:	000a0d74 	.word	0x000a0d74
  511774:	54544147 	.word	0x54544147
  511778:	66654420 	.word	0x66654420
  51177c:	746c7561 	.word	0x746c7561
  511780:	65764520 	.word	0x65764520
  511784:	0a0d746e 	.word	0x0a0d746e
  511788:	2a2a2a00 	.word	0x2a2a2a00
  51178c:	7041202a 	.word	0x7041202a
  511790:	74532070 	.word	0x74532070
  511794:	20747261 	.word	0x20747261
  511798:	2a2a2a2a 	.word	0x2a2a2a2a
  51179c:	000d0a20 	.word	0x000d0a20
  5117a0:	63637573 	.word	0x63637573
  5117a4:	00737365 	.word	0x00737365
  5117a8:	6c696166 	.word	0x6c696166
  5117ac:	00657275 	.word	0x00657275
  5117b0:	65756c42 	.word	0x65756c42
  5117b4:	746f6f74 	.word	0x746f6f74
  5117b8:	6e452068 	.word	0x6e452068
  5117bc:	656c6261 	.word	0x656c6261
  5117c0:	25282064 	.word	0x25282064
  5117c4:	000a2973 	.word	0x000a2973
  5117c8:	61686e55 	.word	0x61686e55
  5117cc:	656c646e 	.word	0x656c646e
  5117d0:	6c422064 	.word	0x6c422064
  5117d4:	6f746575 	.word	0x6f746575
  5117d8:	2068746f 	.word	0x2068746f
  5117dc:	616e614d 	.word	0x616e614d
  5117e0:	656d6567 	.word	0x656d6567
  5117e4:	4520746e 	.word	0x4520746e
  5117e8:	746e6576 	.word	0x746e6576
  5117ec:	7830203a 	.word	0x7830203a
  5117f0:	28207825 	.word	0x28207825
  5117f4:	0a296425 	.word	0x0a296425
  5117f8:	00000000 	.word	0x00000000

005117fc <wiced_bt_cfg_buf_pools>:
  5117fc:	000c0040 00060168 00060420 00000420     @...h... ... ...

0051180c <wiced_bt_cfg_settings>:
  51180c:	0020fb10 00000000 00000003 00120800     .. .............
  51181c:	08000000 00000012 00300060 08000005     ........`.0.....
  51182c:	00050012 00300060 0800001e 001e0012     ....`.0.........
  51183c:	00280018 02bc0000 00300007 001e0030     ..(.......0.0...
  51184c:	04000400 0190003c 00300320 001e0030     ....<... .0.0...
  51185c:	00a000a0 0800001e 00000800 01000200     ................
  51186c:	02030200 00000000 00000000 00000000     ................
  51187c:	03840405 00000c00                       ........

00511884 <BT_LOCAL_NAME_CAPACITY>:
  511884:	                                         ..

00511886 <app_greenhouse_target_target_light_len>:
  511886:	                                         ..

00511888 <app_greenhouse_target_target_temperature_len>:
  511888:	                                         ..

0051188a <app_greenhouse_values_value_light_len>:
  51188a:	                                         ..

0051188c <app_greenhouse_values_value_temperature_len>:
  51188c:	                                         ..

0051188e <app_gap_appearance_len>:
  51188e:	                                         ..

00511890 <app_gap_device_name_len>:
	...

00511892 <app_gatt_db_ext_attr_tbl_size>:
  511892:	                                         ..

00511894 <gatt_database_len>:
  511894:	                                         ..

00511896 <gatt_database>:
  511896:	04020001 18002800 07020002 03022803     .....(.......(..
  5118a6:	032a0000 00020200 0200042a 02280307     ..*.....*.....(.
  5118b6:	2a010005 02020005 00062a01 28000402     ...*.....*.....(
  5118c6:	00071801 28001202 cfd56365 8ddb5d3a     .......(ec..:]..
  5118d6:	e0f64136 31a0e274 15020008 09022803     6A..t..1.....(..
  5118e6:	438d5700 5d21ecd4 844440a1 02e84706     .W.C..!].@D..G..
  5118f6:	82000923 438d5710 5d21ecd4 844440a1     #....W.C..!].@D.
  511906:	02e84706 02000a23 02280315 011a000b     .G..#.....(.....
  511916:	4b9c5b64 4b98baec 19414456 000bed27     d[.K...KVDA.'...
  511926:	011a1082 4b9c5b64 4b98baec 19414456     ....d[.K...KVDA.
  511936:	000ced27 28001202 6b928ba5 b19d8b7a     '......(...kz...
  511946:	85474b12 b9cb292c 1502000d 0e0a2803     .KG.,).......(..
  511956:	bd7ad100 6beb465c 7148efba 8cc5382b     ..z.\F.k..Hq+8..
  511966:	8a000e51 7ad10010 eb465cbd 48efba6b     Q......z.\F.k..H
  511976:	c5382b71 000f518c 28031502 e200100a     q+8..Q.....(....
  511986:	6fb7888b c7a9e2d3 a2c76346 10772d61     ...o....Fc..a-w.
  511996:	00108a00 b7888be2 a9e2d36f c76346c7     ........o....Fc.
  5119a6:	772d61a2                                 .a-w..

005119ac <wiced_platform_init>:
  5119ac:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
  5119ae:	4b20      	ldr	r3, [pc, #128]	; (511a30 <wiced_platform_init+0x84>)
  5119b0:	4d20      	ldr	r5, [pc, #128]	; (511a34 <wiced_platform_init+0x88>)
  5119b2:	4e21      	ldr	r6, [pc, #132]	; (511a38 <wiced_platform_init+0x8c>)
  5119b4:	4798      	blx	r3
  5119b6:	2400      	movs	r4, #0
  5119b8:	1963      	adds	r3, r4, r5
  5119ba:	5d28      	ldrb	r0, [r5, r4]
  5119bc:	7859      	ldrb	r1, [r3, #1]
  5119be:	3402      	adds	r4, #2
  5119c0:	47b0      	blx	r6
  5119c2:	2c18      	cmp	r4, #24
  5119c4:	d1f8      	bne.n	5119b8 <wiced_platform_init+0xc>
  5119c6:	4c1d      	ldr	r4, [pc, #116]	; (511a3c <wiced_platform_init+0x90>)
  5119c8:	4e1d      	ldr	r6, [pc, #116]	; (511a40 <wiced_platform_init+0x94>)
  5119ca:	4f1e      	ldr	r7, [pc, #120]	; (511a44 <wiced_platform_init+0x98>)
  5119cc:	2500      	movs	r5, #0
  5119ce:	6833      	ldr	r3, [r6, #0]
  5119d0:	42ab      	cmp	r3, r5
  5119d2:	f104 040c 	add.w	r4, r4, #12
  5119d6:	d812      	bhi.n	5119fe <wiced_platform_init+0x52>
  5119d8:	4c1b      	ldr	r4, [pc, #108]	; (511a48 <wiced_platform_init+0x9c>)
  5119da:	4e1c      	ldr	r6, [pc, #112]	; (511a4c <wiced_platform_init+0xa0>)
  5119dc:	4f19      	ldr	r7, [pc, #100]	; (511a44 <wiced_platform_init+0x98>)
  5119de:	2500      	movs	r5, #0
  5119e0:	6833      	ldr	r3, [r6, #0]
  5119e2:	42ab      	cmp	r3, r5
  5119e4:	f104 0410 	add.w	r4, r4, #16
  5119e8:	d811      	bhi.n	511a0e <wiced_platform_init+0x62>
  5119ea:	4c19      	ldr	r4, [pc, #100]	; (511a50 <wiced_platform_init+0xa4>)
  5119ec:	4e19      	ldr	r6, [pc, #100]	; (511a54 <wiced_platform_init+0xa8>)
  5119ee:	4f15      	ldr	r7, [pc, #84]	; (511a44 <wiced_platform_init+0x98>)
  5119f0:	2500      	movs	r5, #0
  5119f2:	6833      	ldr	r3, [r6, #0]
  5119f4:	42ab      	cmp	r3, r5
  5119f6:	f104 040c 	add.w	r4, r4, #12
  5119fa:	d810      	bhi.n	511a1e <wiced_platform_init+0x72>
  5119fc:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
  5119fe:	f854 3c0c 	ldr.w	r3, [r4, #-12]
  511a02:	e954 1202 	ldrd	r1, r2, [r4, #-8]
  511a06:	7818      	ldrb	r0, [r3, #0]
  511a08:	47b8      	blx	r7
  511a0a:	3501      	adds	r5, #1
  511a0c:	e7df      	b.n	5119ce <wiced_platform_init+0x22>
  511a0e:	f854 3c10 	ldr.w	r3, [r4, #-16]
  511a12:	e954 1203 	ldrd	r1, r2, [r4, #-12]
  511a16:	7818      	ldrb	r0, [r3, #0]
  511a18:	47b8      	blx	r7
  511a1a:	3501      	adds	r5, #1
  511a1c:	e7e0      	b.n	5119e0 <wiced_platform_init+0x34>
  511a1e:	f854 3c0c 	ldr.w	r3, [r4, #-12]
  511a22:	e954 1202 	ldrd	r1, r2, [r4, #-8]
  511a26:	7818      	ldrb	r0, [r3, #0]
  511a28:	47b8      	blx	r7
  511a2a:	3501      	adds	r5, #1
  511a2c:	e7e1      	b.n	5119f2 <wiced_platform_init+0x46>
  511a2e:	bf00      	nop
  511a30:	000834dd 	.word	0x000834dd
  511a34:	00511b40 	.word	0x00511b40
  511a38:	00083471 	.word	0x00083471
  511a3c:	00511b28 	.word	0x00511b28
  511a40:	00511b24 	.word	0x00511b24
  511a44:	00083271 	.word	0x00083271
  511a48:	00511b14 	.word	0x00511b14
  511a4c:	00511b10 	.word	0x00511b10
  511a50:	00511b10 	.word	0x00511b10
  511a54:	00511b0c 	.word	0x00511b0c

00511a58 <install_libs>:
  511a58:	4770      	bx	lr
	...

00511a5c <application_start_internal>:
  511a5c:	b510      	push	{r4, lr}
  511a5e:	4b04      	ldr	r3, [pc, #16]	; (511a70 <application_start_internal+0x14>)
  511a60:	4798      	blx	r3
  511a62:	4b04      	ldr	r3, [pc, #16]	; (511a74 <application_start_internal+0x18>)
  511a64:	4798      	blx	r3
  511a66:	4b04      	ldr	r3, [pc, #16]	; (511a78 <application_start_internal+0x1c>)
  511a68:	e8bd 4010 	ldmia.w	sp!, {r4, lr}
  511a6c:	4718      	bx	r3
  511a6e:	bf00      	nop
  511a70:	005119ad 	.word	0x005119ad
  511a74:	00272e61 	.word	0x00272e61
  511a78:	005115b9 	.word	0x005115b9

00511a7c <spar_crt_setup>:
  511a7c:	b513      	push	{r0, r1, r4, lr}
  511a7e:	4813      	ldr	r0, [pc, #76]	; (511acc <spar_crt_setup+0x50>)
  511a80:	4913      	ldr	r1, [pc, #76]	; (511ad0 <spar_crt_setup+0x54>)
  511a82:	4c14      	ldr	r4, [pc, #80]	; (511ad4 <spar_crt_setup+0x58>)
  511a84:	2307      	movs	r3, #7
  511a86:	4288      	cmp	r0, r1
  511a88:	f88d 3007 	strb.w	r3, [sp, #7]
  511a8c:	d001      	beq.n	511a92 <spar_crt_setup+0x16>
  511a8e:	4a12      	ldr	r2, [pc, #72]	; (511ad8 <spar_crt_setup+0x5c>)
  511a90:	47a0      	blx	r4
  511a92:	4a12      	ldr	r2, [pc, #72]	; (511adc <spar_crt_setup+0x60>)
  511a94:	4b12      	ldr	r3, [pc, #72]	; (511ae0 <spar_crt_setup+0x64>)
  511a96:	4813      	ldr	r0, [pc, #76]	; (511ae4 <spar_crt_setup+0x68>)
  511a98:	2100      	movs	r1, #0
  511a9a:	4798      	blx	r3
  511a9c:	4b12      	ldr	r3, [pc, #72]	; (511ae8 <spar_crt_setup+0x6c>)
  511a9e:	4a13      	ldr	r2, [pc, #76]	; (511aec <spar_crt_setup+0x70>)
  511aa0:	f023 030f 	bic.w	r3, r3, #15
  511aa4:	6013      	str	r3, [r2, #0]
  511aa6:	4b12      	ldr	r3, [pc, #72]	; (511af0 <spar_crt_setup+0x74>)
  511aa8:	4798      	blx	r3
  511aaa:	b910      	cbnz	r0, 511ab2 <spar_crt_setup+0x36>
  511aac:	4b11      	ldr	r3, [pc, #68]	; (511af4 <spar_crt_setup+0x78>)
  511aae:	4a12      	ldr	r2, [pc, #72]	; (511af8 <spar_crt_setup+0x7c>)
  511ab0:	601a      	str	r2, [r3, #0]
  511ab2:	2201      	movs	r2, #1
  511ab4:	f10d 0107 	add.w	r1, sp, #7
  511ab8:	4810      	ldr	r0, [pc, #64]	; (511afc <spar_crt_setup+0x80>)
  511aba:	47a0      	blx	r4
  511abc:	4b10      	ldr	r3, [pc, #64]	; (511b00 <spar_crt_setup+0x84>)
  511abe:	4798      	blx	r3
  511ac0:	4b10      	ldr	r3, [pc, #64]	; (511b04 <spar_crt_setup+0x88>)
  511ac2:	4a11      	ldr	r2, [pc, #68]	; (511b08 <spar_crt_setup+0x8c>)
  511ac4:	601a      	str	r2, [r3, #0]
  511ac6:	b002      	add	sp, #8
  511ac8:	bd10      	pop	{r4, pc}
  511aca:	bf00      	nop
  511acc:	0020fac0 	.word	0x0020fac0
  511ad0:	0020fac0 	.word	0x0020fac0
  511ad4:	00006d31 	.word	0x00006d31
  511ad8:	0000005d 	.word	0x0000005d
  511adc:	00000002 	.word	0x00000002
  511ae0:	00006d41 	.word	0x00006d41
  511ae4:	0020fb20 	.word	0x0020fb20
  511ae8:	0020fb42 	.word	0x0020fb42
  511aec:	00200464 	.word	0x00200464
  511af0:	0007e6a5 	.word	0x0007e6a5
  511af4:	00200be4 	.word	0x00200be4
  511af8:	002031f4 	.word	0x002031f4
  511afc:	00200bae 	.word	0x00200bae
  511b00:	00511a59 	.word	0x00511a59
  511b04:	00206260 	.word	0x00206260
  511b08:	00511a5d 	.word	0x00511a5d

00511b0c <gpio_count>:
  511b0c:	00000000                                ....

00511b10 <button_count>:
  511b10:	00000001                                ....

00511b14 <platform_button>:
  511b14:	00511b40 00000400 00000001 00000000     @.Q.............

00511b24 <led_count>:
  511b24:	00000002                                ....

00511b28 <platform_led>:
  511b28:	00511b4e 00004400 00000001 00511b4c     N.Q..D......L.Q.
  511b38:	00004400 00000001                       .D......

00511b40 <platform_gpio_pins>:
  511b40:	0f060000 0d090008 10110e0b 001b001a     ................
  511b50:	021d011c 21252020                       ....  %!
