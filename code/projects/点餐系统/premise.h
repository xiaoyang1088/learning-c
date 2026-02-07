#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define Max_store 20
#define Max_table 50
#define Max_dish 30
#define User_file "users.dat"  //普通客户文件
#define Vip_file "vips.dat"    //Vip客户文件
#define Store_file "stores.dat"  //门店文件

extern char Merchant_password[20];




//菜品结构体
typedef struct {
	char name[20];
	float init_price;
	int stock;
}Dish;

//门店结构体
typedef struct {
	char name[20];
	char didian[20];
	char dianzhang[20];
	char dianhua[20];
	int table_count;
	int table[Max_table];
	Dish dishs[20];
	int dish_count;
	int user_count;
}Store;


//用户结构体（临时）
typedef struct {
	char dian_name[20];
	char vip[10];
	int table;  
}User;

//会员结构体
typedef struct {
	char id[20];
	char psw[20];
	int denji;
}Vip;

int load_vip(Vip vips[], int* vip_count);

void save_vips(Vip vips[], int vip_count);

void add_vips(Vip vips[],int *vip_count);

void save_stores(Store stores[], int store_count);

void init_store(Store stores[], int* store_count);

int  init_user(User users[], int* user_count, int store_count, Store stores[]);

void save_user(User users[], int user_count, int store_count, Store stores[]);

void show_dishs(Store stores[], int dish_count, int store_num);


void merchant_system(Store stores[], int* store_count, User users[], int* user_count);

void show_stores(Store stores[], int store_count);

void mendian_system(Store stores[], int choice1, int dish_count, int store_count, User users[], int* user_count);

void show_only_median(Store stores[], int choice1);

void table_print(Store stores[], int option);

void user_system(Store stores[], int store_count, int* user_count, Vip vips[], int* vip_count);

int pay_system(float all_money);

void Is_a_vip(User* now_user, Vip vips[], int* vip_count);

void add_mendian(int* store_count, Store stores[]);
