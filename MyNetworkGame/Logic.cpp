
int  CheckResult(int a1, int a2){
	//38 ±¤¶¯
	if (a1 == 14 && a2 == 4)
		return 100;
	//±¤¶¯ 1+3¿ù
	if (a1 == 18 && a2 == 14)
		return 99;
	//±¤¶¯ 1+8¿ù
	if (a1 == 18 && a2 == 4)
		return 99;
	//Àå¶¯ (10¿ù)
	if (a1 == 0 && a2 == 1)
		return 98;
	//9¿ù ¶¯
	if (a1 == 2 && a2 == 3)
		return 97;
	//8¿ù¶¯
	if (a1 == 4 && a2 == 5)
		return 96;
	//7¿ù¶¯
	if (a1 == 6 && a2 == 7)
		return 95;
	//6¿ù¶¯
	if (a1 == 8 && a2 == 9)
		return 94;
	//5¿ù¶¯
	if (a1 == 10 && a2 == 11)
		return 93;
	//4¿ù¶¯
	if (a1 == 12 && a2 == 13)
		return 92;
	//3¿ù¶¯
	if (a1 == 14 && a2 == 15)
		return 91;
	//2¿ù¶¯
	if (a1 == 16 && a2 == 17)
		return 90;
	//»±¶¯ (1¿ù)
	if (a1 == 18 && a2 == 19)
		return 89;
	//¾Ë¸® (1¿ù + 2¿ù)
	if (a1 == 18 && a2 == 16)
		return 88;
	if (a1 == 18 && a2 == 17)
		return 88;
	if (a1 == 19 && a2 == 16)
		return 88;
	if (a1 == 19 && a2 == 17)
		return 88;
	//µ¶»ç (1¿ù + 4¿ù)
	if (a1 == 18 && a2 == 12)
		return 87;
	if (a1 == 18 && a2 == 13)
		return 87;
	if (a1 == 19 && a2 == 12)
		return 87;
	if (a1 == 19 && a2 == 13)
		return 87;
	//±¸»æ (1¿ù + 9¿ù)
	if (a1 == 18 && a2 == 2)
		return 86;
	if (a1 == 18 && a2 == 3)
		return 86;
	if (a1 == 19 && a2 == 2)
		return 86;
	if (a1 == 19 && a2 == 3)
		return 86;
	//Àå»æ (1¿ù + 10¿ù)
	if (a1 == 18 && a2 == 0)
		return 85;
	if (a1 == 18 && a2 == 1)
		return 85;
	if (a1 == 19 && a2 == 0)
		return 85;
	if (a1 == 19 && a2 == 1)
		return 85;
	//Àå»ç (4¿ù + 10¿ù)
	if (a1 == 12 && a2 == 0)
		return 84;
	if (a1 == 12 && a2 == 1)
		return 84;
	if (a1 == 13 && a2 == 0)
		return 84;
	if (a1 == 13 && a2 == 1)
		return 84;
	//¼¼·ú (4¿ù + 6¿ù)
	if (a1 == 12 && a2 == 8)
		return 83;
	if (a1 == 12 && a2 == 9)
		return 83;
	if (a1 == 13 && a2 == 8)
		return 83;
	if (a1 == 13 && a2 == 9)
		return 83;
	//°©¿À (µÎ ÀåÀÇ ÇÕÇÑ ¼öÀÇ ³¡ÀÚ¸® ¼ö°¡ 9ÀÎ °æ¿ì)(1,8)(2,7)(3,6)(4,5)(10,9)(±¤¶¯ Á¦¿Ü)

	if (a1 == 18 && a2 == 5)
		return 82;
	if (a1 == 19 && a2 == 4)
		return 82;
	if (a1 == 19 && a2 == 5)
		return 82;

	if (a1 == 16 && a2 == 6)
		return 82;
	if (a1 == 16 && a2 == 7)
		return 82;
	if (a1 == 17 && a2 == 6)
		return 82;
	if (a1 == 17 && a2 == 7)
		return 82;

	if (a1 == 14 && a2 == 8)
		return 82;
	if (a1 == 14 && a2 == 9)
		return 82;
	if (a1 == 15 && a2 == 8)
		return 82;
	if (a1 == 15 && a2 == 9)
		return 82;

	if (a1 == 12 && a2 == 10)
		return 82;
	if (a1 == 12 && a2 == 11)
		return 82;
	if (a1 == 13 && a2 == 10)
		return 82;
	if (a1 == 13 && a2 == 11)
		return 82;

	if (a1 == 0 && a2 == 2)
		return 82;
	if (a1 == 0 && a2 == 3)
		return 82;
	if (a1 == 0 && a2 == 2)
		return 82;
	if (a1 == 0 && a2 == 3)
		return 82;
	//8²ı (1,7)(2,6)(3,5)(10,8)
	if (a1 == 18 && a2 == 6)
		return 81;
	if (a1 == 18 && a2 == 7)
		return 81;
	if (a1 == 19 && a2 == 6)
		return 81;
	if (a1 == 19 && a2 == 7)
		return 81;

	if (a1 == 16 && a2 == 8)
		return 81;
	if (a1 == 16 && a2 == 9)
		return 81;
	if (a1 == 17 && a2 == 8)
		return 81;
	if (a1 == 17 && a2 == 9)
		return 81;

	if (a1 == 14 && a2 == 10)
		return 81;
	if (a1 == 14 && a2 == 11)
		return 81;
	if (a1 == 15 && a2 == 10)
		return 81;
	if (a1 == 15 && a2 == 11)
		return 81;

	if (a1 == 0 && a2 == 4)
		return 81;
	if (a1 == 0 && a2 == 5)
		return 81;
	if (a1 == 1 && a2 == 4)
		return 81;
	if (a1 == 1 && a2 == 5)
		return 81;
	//7²ı (1,6)(2,5)(3,4)(10,7)
	if (a1 == 18 && a2 == 8)
		return 80;
	if (a1 == 18 && a2 == 9)
		return 80;
	if (a1 == 19 && a2 == 8)
		return 80;
	if (a1 == 19 && a2 == 9)
		return 80;

	if (a1 == 16 && a2 == 10)
		return 80;
	if (a1 == 16 && a2 == 11)
		return 80;
	if (a1 == 17 && a2 == 10)
		return 80;
	if (a1 == 17 && a2 == 11)
		return 80;

	if (a1 == 14 && a2 == 12)
		return 80;
	if (a1 == 14 && a2 == 13)
		return 80;
	if (a1 == 15 && a2 == 12)
		return 80;
	if (a1 == 15 && a2 == 13)
		return 80;

	if (a1 == 0 && a2 == 6)
		return 80;
	if (a1 == 0 && a2 == 7)
		return 80;
	if (a1 == 1 && a2 == 6)
		return 80;
	if (a1 == 1 && a2 == 7)
		return 80;
	//6²ı (1,5)(2,4)(10,6)
	if (a1 == 18 && a2 == 10)
		return 79;
	if (a1 == 18 && a2 == 11)
		return 79;
	if (a1 == 19 && a2 == 10)
		return 79;
	if (a1 == 19 && a2 == 11)
		return 79;

	if (a1 == 16 && a2 == 12)
		return 79;
	if (a1 == 16 && a2 == 13)
		return 79;
	if (a1 == 17 && a2 == 12)
		return 79;
	if (a1 == 17 && a2 == 13)
		return 79;

	if (a1 == 0 && a2 == 8)
		return 79;
	if (a1 == 0 && a2 == 9)
		return 79;
	if (a1 == 1 && a2 == 8)
		return 79;
	if (a1 == 1 && a2 == 9)
		return 79;
	//5²ı (2,3)(10,5)
	if (a1 == 16 && a2 == 14)
		return 76;
	if (a1 == 16 && a2 == 15)
		return 76;
	if (a1 == 17 && a2 == 14)
		return 76;
	if (a1 == 17 && a2 == 15)
		return 76;

	if (a1 == 0 && a2 == 10)
		return 76;
	if (a1 == 0 && a2 == 11)
		return 76;
	if (a1 == 1 && a2 == 10)
		return 76;
	if (a1 == 1 && a2 == 11)
		return 76;
	//4²ı (1,3)(±¤³¢¸® ¸¸³ª´Â°Ç Á¦¿Ü) (5,9)
	if (a1 == 18 && a2 == 15)
		return 75;
	if (a1 == 19 && a2 == 14)
		return 75;
	if (a1 == 19 && a2 == 15)
		return 75;

	if (a1 == 10 && a2 == 2)
		return 75;
	if (a1 == 10 && a2 == 3)
		return 75;
	if (a1 == 11 && a2 == 2)
		return 75;
	if (a1 == 11 && a2 == 3)
		return 75;
	//3²ı (10,3)(5,8)
	if (a1 == 0 && a2 == 14)
		return 74;
	if (a1 == 0 && a2 == 15)
		return 74;
	if (a1 == 1 && a2 == 14)
		return 74;
	if (a1 == 1 && a2 == 15)
		return 74;

	if (a1 == 10 && a2 == 4)
		return 73;
	if (a1 == 10 && a2 == 5)
		return 73;
	if (a1 == 11 && a2 == 4)
		return 73;
	if (a1 == 11 && a2 == 5)
		return 73;
	//2²ı (10,2)(5,7)
	if (a1 == 0 && a2 == 16)
		return 72;
	if (a1 == 0 && a2 == 17)
		return 72;
	if (a1 == 1 && a2 == 16)
		return 72;
	if (a1 == 1 && a2 == 17)
		return 72;

	if (a1 == 10 && a2 == 6)
		return 72;
	if (a1 == 10 && a2 == 7)
		return 72;
	if (a1 == 11 && a2 == 6)
		return 72;
	if (a1 == 11 && a2 == 7)
		return 72;
	//1²ı (5,6)
	if (a1 == 10 && a2 == 8)
		return 71;
	if (a1 == 10 && a2 == 9)
		return 71;
	if (a1 == 11 && a2 == 8)
		return 71;
	if (a1 == 11 && a2 == 9)
		return 71;

	//¸ÁÅë (2¿ù + 8¿ù)
	if (a1 == 16 && a2 == 4)
		return 70;
	if (a1 == 16 && a2 == 5)
		return 70;
	if (a1 == 17 && a2 == 4)
		return 70;
	if (a1 == 17 && a2 == 5)
		return 70;
	//Æ¯¼ö Á·º¸ °í·Á ¾ÈÇÔ(ÀüºÎ ²ıÀ¸·Î Ã³¸®)
	return 70;


}