#include "premise.h"
Store stores[20];
User users[100];
Vip vips[100];


//加载VIP信息

int load_vip(Vip vips[], int* vip_count) {
	FILE* fp = fopen(Vip_file, "rb");

	if (fp != NULL) {
		fread(vip_count, sizeof(int), 1, fp);
		fread(vips, sizeof(Vip), *vip_count, fp);
		fclose(fp);
		return 1;
	}
	*vip_count = 1;
	strcpy(vips[0].psw, "25020001");
	strcpy(vips[0].id, "25020001");
	vips[0].denji= 1;
	fp = fopen(Vip_file, "wb");
	fwrite(vip_count, sizeof(int), 1, fp);
	fwrite(vips, sizeof(Vip), *vip_count, fp);
	fclose(fp);
	save_vips(vips, *vip_count);
	return 1;
}

//保存Vip信息到文件_
void save_vips(Vip vips[], int vip_count) {
	FILE* fp = fopen(Vip_file, "wb");
	if (fp == NULL) {
		printf("Vip信息保存失败！\n");
		return;
	}
	fwrite(&vip_count, sizeof(int), 1, fp);
	fwrite(vips, sizeof(Vip), vip_count, fp);
	fclose(fp);
	printf("Vip信息已经保存!\n");
	
}

//添加Vip用户
void add_vips(Vip vips[], int *vip_count) {
	load_vip(vips, vip_count);  //加载已有Vip

	Vip new_vip;
	printf("请输入卡号:");
	scanf("%s", new_vip.id);
	for (int i = 0; i < *vip_count; i++) {
		if (strcmp(vips[i].id, new_vip.id) == 0) {
			printf("该账号已经被注册！\n");
			return;
		}
	}
	printf("请输入密码：");
	scanf("%s", new_vip.psw);
	printf("请输入等级：");
	scanf("%d", &new_vip.denji);
	vips[*vip_count] = new_vip;
	(*vip_count)++;
	save_vips(vips, *vip_count);
	printf("新Vip客户添加成功！账号是：%s,等级为：%d\n", new_vip.id, new_vip.denji);
}

//门店保存文件函数
void save_stores(Store stores[], int store_count) {
	FILE* fp = fopen(Store_file, "wb");
	if (fp == NULL) {
		printf("文件保存失败！\n");
		return;
	}
	fwrite(&store_count, sizeof(int), 1, fp);
	fwrite(stores, sizeof(Store), store_count, fp);
	fclose(fp);
	printf("门店数据保存成功\n");
	return;
}

//初始化门店数据
void init_store(Store stores[], int* store_count) {
	FILE* fp = fopen(Store_file, "rb");
	if (fp != NULL) {
		fread(store_count, sizeof(int), 1, fp);
		fread(stores, sizeof(Store), *store_count, fp);
		fclose(fp);
		return;
	}
	*store_count = 1;
	stores[0].dish_count = 1;
	strcpy(stores[0].name, "德阳什邡小广场店");
	strcpy(stores[0].dianzhang, "雷钧富");
	strcpy(stores[0].dianhua, "13525252222");
	strcpy(stores[0].didian, "中立嘉苑A区");
	stores[0].table_count = 10;
	for (int i = 0; i < stores[0].table_count; i++) {
		stores[0].table[i] = 0;
	}
	strcpy(stores[0].dishs[0].name, "苹果清茉");
	stores[0].dishs[0].init_price = 9.9;
	stores[0].dishs[0].stock = 15;
	save_stores(stores, *store_count);
}





//显示所有商品界面
void show_dishs(Store stores[],int dish_count,int store_num) {
	printf("\n==============商品列表==============\n");
	printf("序号\t  名称\t\t单价\t库存\n");
	for (int i = 0; i < dish_count; i++) {
		printf("%d\t%8s\t%.1f\t%d\n", i + 1,stores[store_num].dishs[i].name,stores[store_num].dishs[i].init_price,stores[store_num].dishs[i].stock);
	}
	printf("====================================\n");
}

//商家管理界面
void merchant_system(Store stores[], int* store_count,User users[],int *user_count) {
	char password[20];
	printf("\n=====商家管理验证系统=====\n");
	printf("请输入系统密码：");
	scanf("%s",password);
	if (strcmp(password, Merchant_password) != 0) {
		printf("密码错误!\n无权进入商家！\n");
		return;
	}
	int choice=0,choice1=0;
	while (1) {
		printf("\n======商家管理界面======\n");
		printf("1.选择门店\n");
		printf("2.增加门店\n");
		printf("0.退出管理系统\n");
		printf("选择服务：");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			show_stores(stores, *store_count);
			printf("请选择门店:\n");
			scanf("%d", &choice1);
			if (choice1<1 || choice1>*store_count) {
				printf("选择无效！\n");
				break;
			}
			choice1 -= 1;
			show_only_median(stores, choice1);
			
			mendian_system(stores, choice1, stores[choice1].dish_count, *store_count, users, user_count);
			break;
		case 2:
			add_mendian(store_count,stores);
			printf("添加成功！");
			break;
		case 0:
			return;
		default:
			printf("输入不符合规范，请重新输入！\n");
			break;
		}
	}
	
}

//显示门店
void show_stores(Store stores[], int store_count) {
	printf("\n======门店如下======\n");
	for (int i = 0; i < store_count; i++) {
		printf("%d\t%20s\t\t%20s\n", i + 1, stores[i].name, stores[i].didian);

	}
	printf("======================\n");
}

//显示单一门店信息
void show_only_median(Store stores[], int choice1) {
	printf("\n=======您选择的门店信息如下========\n");
	printf("%d\t%s\n", 1, stores[choice1].name);
	printf("%d\t%s\n", 2, stores[choice1].dianzhang);
	printf("%d\t%s\n", 3, stores[choice1].dianhua);
	printf("%d\t%s\n", 4, stores[choice1].didian);
	for (int i = 0; i <stores[choice1].dish_count; i++) {
		printf("%d\t%8s\t%.1f\t%d\n", i + 5, stores[choice1].dishs[i].name, stores[choice1].dishs[i].init_price, stores[choice1].dishs[i].stock);
	}
	printf("====================================\n");
}

//门店管理系统
void mendian_system(Store stores[], int choice1, int dish_count, int store_count, User users[], int* user_count) {
	int choice2;
	int go_back;
	while (1) {
		printf("\n请选择您想要的服务：\n");
		printf("1.增加食品种类\n");
		printf("2.增加库存\n");
		printf("3.修改价格\n");
		printf("4.移除已走客户\n");
		printf("0.退回上一页\n");
		scanf("%d", &choice2);
		switch (choice2)
		{
		case 1:
			show_dishs(stores, stores[choice1].dish_count, choice1);
			if (dish_count >= Max_dish) {
				printf("食品种类已经达到上限，不能添加更多商品！\n");
				break;
			}
			Dish new_dish;
			printf("请输入新品名称:");
			scanf("%s", new_dish.name);
			printf("请输入新品初始价格:");
			scanf("%f", &new_dish.init_price);
			printf("请输入初始库存：");
			scanf("%d", &new_dish.stock);
			stores[choice1].dishs[stores[choice1].dish_count] = new_dish;
			stores[choice1].dish_count++;
			save_stores(stores, store_count);
			printf("添加新品成功！\n");
			break;


			
		case 2:
			
			show_dishs(stores, stores[choice1].dish_count, choice1);
			int idx, add_num;
			printf("输入要补充的商品序号：");
			scanf("%d", &idx);
			if (idx<1 || idx>stores[choice1].dish_count) {
				printf("输入无效，请重新输入！\n");
				break;
			}
			idx -= 1;
			printf("要补充的数量是：");
			scanf("%d", &add_num);
			if(add_num<1){
				printf("数量无效！\n");
				break;
			}
			stores[choice1].dishs[idx].stock += add_num;
			save_stores(stores, store_count);
			printf("库存补充成功，%s当前库存为：%d\n", stores[choice1].dishs[idx].name,
				stores[choice1].dishs[idx].stock);
			break;

		case 3:
			show_dishs(stores,  stores[choice1].dish_count,choice1);
			int idx2;
			float new_price;
			printf("输入要补充的商品序号：");
			scanf("%d", &idx2);
			if (idx2<1 || idx2>stores[choice1].dish_count) {
				printf("输入无效，请重新输入！\n");
				break;
			}
			idx2 -= 1;
			printf("要修改的价格是：");
			scanf("%f", &new_price);
			if (new_price <=0) {
				printf("价格无效！\n");
				break;
			}
			stores[choice1].dishs[idx2].init_price = new_price;
			save_stores(stores, store_count);
			printf("价格修改成功！%s新单价为：%.1f\n", stores[choice1].dishs[idx2].name, 
				stores[choice1].dishs[idx2].init_price);
			break;
		case 4:
			printf("第几桌客户离去：");
			scanf("%d", &go_back);
			if (go_back < 1 || go_back > stores[choice1].table_count) {
				printf("桌位号无效！\n");
				break;
			}
			go_back--;
			stores[choice1].table[go_back] = 0;
			(*user_count)--;
			stores[choice1].user_count -= 1;
			save_stores(stores, store_count);
			save_user(users, user_count, store_count, stores);
			break;
		case 0:
			return;
		default:
			printf("输入不符合规范，请重新输入!\n");
			break;
		}
	}
	
}


//普通用户初始化
int  init_user(User users[], int* user_count,int store_count,Store stores[]) {
	FILE* fp = fopen(User_file, "rb");
	if (fp != NULL) {
		fread(user_count, sizeof(int), 1, fp);
		fread(users, sizeof(User), *user_count, fp);
		fclose(fp);
		return 1;
	}
	*user_count = 1;
	stores[0].user_count = 1;
	strcpy(users[0].dian_name, "德阳什邡小广场店");
	strcpy(users[0].vip, "是");
	users[0].table = 1;
	stores[0].table[0] = 1;
	save_user(users, *user_count,store_count,stores);
	save_stores(stores, store_count);
	return 0;
}

//普通用户保存函数

void save_user(User users[], int user_count,int store_count,Store stores[]) {
	FILE* fp = fopen(User_file, "wb");
	if (fp == NULL) {
		printf("用户信息保存失败！\n");
		return;
	}
	fwrite(&user_count, sizeof(int), 1, fp);
	fwrite(users, sizeof(User), user_count, fp);
	
	fclose(fp);
	save_stores(stores, store_count);
	printf("用户信息已保存！\n");
}

void Is_a_vip(User* now_user, Vip vips[], int* vip_count) {
	int option1;
	Vip now_vip;
	int option4;
	IS:
	printf("您是否是会员（若是输入1，不是输入2）：");
	scanf("%d", &option1);
	switch (option1)
	{
	case 1:
		NEW:
		printf("请输入您的账号和密码");
		scanf("%s%s", now_vip.id, now_vip.psw);
		for (int i = 0; i < *vip_count; i++) {
			if ((strcmp(now_vip.id, vips[i].id) == 0) && ((strcmp(now_vip.psw, vips[i].psw) == 0))) {
			strcpy(now_user->vip, "是");
			printf("欢迎回家，尊贵的会员！");
			goto YES;
			}   
		}
		printf("账号或密码输入错误，请重新输入！\n");
		goto IS;
		YES:
		break;
	case 2:
		printf("您想要注册会员吗？会费20元一个月，可享受8折优惠！");
		printf("\n如果想，输入1！");
		scanf("%d", &option4);
		if (option4 == 1) {
			add_vips(vips,vip_count);
			goto NEW;
		}
		strcpy(now_user->vip, "否");
		break;

	default:
		printf("输入无效！\n");
		goto IS;
		break;
	}
}
int pay_system(float all_money) {
	printf("确认支付（y/n）:");
	char t;
	while (getchar() != '\n');
	scanf("%c", &t);
	if (t == 'y') {
		printf("支付成功!\n");
		return 1;
	}
	else if (t == 'n') {
		printf("支付失败！\n");
		return 2;
	}
	else {
		printf("无效操作！\n");
		return 2;
	}
		
}

void user_system(Store stores[], int store_count, int* user_count, Vip vips[], int* vip_count) {
	int option,option1;
	User now_user;
	show_stores(stores, store_count);
	printf("请选择您想要选择的店铺：");
	scanf("%d", &option);
	option -= 1;
	strcpy(now_user.dian_name, stores[option].name);
	Is_a_vip(&now_user, vips, vip_count);
	show_dishs(stores, stores[option].dish_count, option);
	printf("选择您想要购买的食品:");
	scanf("%d", &option1);
	option1 -= 1;
	if (option1 < 0 || option1 >= stores[option].dish_count) {
		printf("菜品编号无效！\n");
		return;
	}
	float all_money=0;
	if (strcmp(now_user.vip, "是") == 0) {
		printf("请支付：%.1f元", (stores[option].dishs[option1].init_price)*0.8);
		all_money = (stores[option].dishs[option1].init_price) * 0.8;
	}
	else {
		printf("请支付：%.1f元", stores[option].dishs[option1].init_price);
		all_money = stores[option].dishs[option1].init_price;
	}
	int pay=pay_system(all_money);
	Start:
	if (pay == 1) {
		int option2;
		printf("1.外带\n");
		printf("2.堂食\n");
		printf("您想外带还是在店享用:");
		scanf("%d", &option2);
		if (option2 == 1) {
			now_user.table = 0;
			return;
		}
		else if (option2 == 2) {
			if (stores[option].user_count > stores[option].table_count) {
				printf("座位已满，请等待或者外带！\n");
				goto Start;
			}
			table_print(stores, option);
			int option3;
			printf("\n请选择座位（0代表可预约）:");
			scanf("%d", &option3);
			option3 -= 1;
			if (stores[option].table[option3] == 1) {
				printf("已被占用，请重新选择！\n");
				goto Start;
			}
			stores[option].table[option3] = 1;
			now_user.table = 1;
			users[option3] = now_user;
			(stores[option].user_count)++;
			save_stores(stores, store_count);
			save_user(users, *user_count, store_count, stores);
			printf("\n选择成功，请前往%d号座位就坐！",option3+1);
			return;
		}
	}
	else if (pay == 2) {
		return;
	}
	
	
}

void table_print(Store stores[], int option) {
	printf("======剩余座位如下======\n");
	for (int i = 0; i < stores[option].table_count; i++) {
		printf("%d ", i+1);
	}
	printf("\n");
	for (int i = 0; i < stores[option].table_count; i++) {
		printf("%d ", stores[option].table[i]);
	}
}

void add_mendian(int *store_count,Store stores[]) {
	Store new_store;
	NAME:
	printf("请输入门店名字:");
	
	scanf("%s", new_store.name);
	for (int i = 0; i < *store_count; i++) {
		if (strcmp(new_store.name, stores[i].name) == 0) {
			printf("店面已经存在，请重新命名！\n");
			goto NAME;
		}
	}		
	printf("请输入地点：");
	scanf("%s", new_store.didian);
	printf("请输入店长：");
	scanf("%s", new_store.dianzhang);
	printf("请输入电话：");
	scanf("%s", new_store.dianhua);
	printf("输入座位数：");
	scanf("%d", &new_store.table_count);
	new_store.dish_count = 0;
	new_store.user_count = 0;
	for (int i = 0; i < new_store.table_count; i++) {
		new_store.table[i] = 0;
	}
	stores[*store_count] = new_store;
	(*store_count)++;
	save_stores(stores, *store_count);
	return;
}



























