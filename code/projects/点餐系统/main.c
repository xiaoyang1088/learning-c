#include "premise.h"
char Merchant_password[20] = "123456";
int main() {
	int choice=-1;
	Store stores[Max_store];
	int store_count=0;
	init_store(stores, &store_count);
	User users[Max_table];
	int user_count = 0;
	init_user(users, &user_count, store_count, stores);
	Vip vips[100];
	int vip_count = 0;
	load_vip(vips, &vip_count);
	while (1) {
		printf("\n=======欢迎光临‘沪上阿姨’=======\n");
		printf("选择您想要的服务\n");
		printf("1.用户\n");
		printf("2.商家\n");
		printf("0.退出程序\n");
		printf("请选择功能：");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:user_system(stores, store_count, &user_count, vips, &vip_count);
			break;
		case 2:
			merchant_system(stores,&store_count,users,&user_count);
			break;
		case 0:
			exit(0);

		default:
			printf("无效输入！请重新输入！");
			break;
		}
	}
	return 0;
}
