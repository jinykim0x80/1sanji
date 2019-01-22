#pragma once
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/system.h>
#include <eosiolib/serialize.hpp>


// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
using namespace eosio;

class onesanji : contract {
using contract::contract;
private:
	/// abi table 

	struct [[eosio::table]] black_proof{
		uint64_t order_no;						// uniquekey
		std::string brand;					// 브랜드
		std::string kind;					
		std::string volume;					// 용량
		uint32_t price;					// 가격
		std::string producer;				// 생산자
		std::string locate_address;			// 지역주소
		uint32_t insurance_day;		    // 데이터 보장기간 yymmdd < 2^32

		auto primary_key() const { return order_no; }	
		auto get_insurance_day() const { return insurance_day; }
	
		uint32_t harvest_day;				// 수확일
		uint32_t cutting_day;				// 도정일
		EOSLIB_SERIALIZE(black_proof, (order_no)(brand)(kind)(volume)(price)(producer)(locate_address)(insurance_day)(harvest_day)(cutting_day))
	};
	struct [[eosio::table]] gold_proof{
		uint64_t order_no;						// uniquekey
		std::string brand;					// 브랜드
		std::string kind;					
		std::string volume;					// 용량
		uint32_t price;					// 가격
		std::string producer;				// 생산자
		std::string locate_address;			// 지역주소
		uint32_t insurance_day;		    // 데이터 보장기간 yymmdd < 2^32
		uint32_t harvest_day;				// 수확일
		uint32_t cutting_day;				// 도정일
		std::string recipient;				// 받는사람
		uint32_t phone_number;	        // 휴대폰번호 뒷자리 
		auto get_phone_number() const { return phone_number; }

		auto primary_key() const { return order_no; }	
		auto get_insurance_day() const { return insurance_day; }
		EOSLIB_SERIALIZE(gold_proof, (order_no)(brand)(kind)(volume)(price)(producer)(locate_address)(insurance_day)(harvest_day)(cutting_day)(recipient)(phone_number))
	};

	typedef eosio::multi_index<"gold_proof"_n, gold_proof> gold_rice;
	typedef eosio::multi_index<"black_proof"_n, black_proof> black_rice;
	//grice_index rice_gold_table;
	/*
	void check(){
		//eosio_assert(rice_gold_table.get_code() == "tester"_n, "You don't access");
	}
	*/
public:
	onesanji(account_name self) : contract(self)/*, rice_gold_table(self, self) */{}

	[[eosio::action]] void addrice(
		uint64_t& order_no, 
		std::string& brand, 
		std::string& kind, 
		std::string& volume, 
		uint32_t& price, 
		std::string& producer, 
		std::string& locate_address,
		uint32_t& insurance_day,
		uint32_t& harvest_day,
		uint32_t& cutting_day,
		std::string& recipient,
		uint32_t& phone_number);
	// for black
	// /*
//	[[eosio::action]] void addRice(
//		std::string /*order_no*/, 
//		std::string /*brand*/, 
//		std::string /*kind*/, 
//		std::string /*volume*/, 
//		size_t /*price*/, 
//		std::string /*producer*/, 
//		std::string /*locate_address*/,
//		std::string /*insurance_day*/			// insurance_day casting to uint32_t
//	);					
//
//	// for gold 
//	[[eosio::action]] void addRice(
//		std::string /*order_no*/, 
//		std::string /*brand*/, 
//		std::string /*kind*/, 
//		std::string /*volume*/, 
//		size_t /*price*/, 
//		std::string /*producer*/, 
//		std::string /*locate_address*/,
//		std::string /*insurance_day*/,			// insurance_day casting to uint32_t
//		std::string /*harvest_day*/,
//		std::string /*cutting_day*/,
//		std::string /*recipient*/,
//		uint32_t /*phone_number*/
//	); 
//
	[[eosio::action]] void delrice(uint64_t&/*order_no*/, const std::string& /*qrtype*/);
//	[[eosio::action]] void collectResource();
	[[eosio::action]] void viewrice(uint64_t& /*order_no*/, const std::string& /*qrtype*/);
	[[eosio::action]] void printalltable();
	/*
	const int currentDateTime(){
		timet     now = std::clock();
		struct tm  tstruct;
		char       buf[8];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%g%m%d", &tstruct);

		return atoi(buf);
	}
	*/
};

