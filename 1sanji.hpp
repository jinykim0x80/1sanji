#pragma once
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/system.h>
#include <eosiolib/serialize.hpp>
#include <chrono>
#include <ctime>
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
//////////////////////////////////////////////////////////////////////////////////////////////
//
	uint32_t get_date() const{									// UTC based.
		/*
		time_t t = time(NULL);
		char       buf[8];									// if we support long term something as wine. it must be changed.
		struct tm  tstruct = *gmtime(&t);;
		strftime(buf, sizeof(buf), "%g%m%d", &tstruct);
		return atoi(buf);
		*/
		return 0;
	}

public:
	onesanji(account_name self) : contract(self) { /* constructor */  }

	[[eosio::action]] void addrice(
		const uint64_t& /*order_no*/, 
		const std::string& /*qrtype*/,
		const std::string& /*brand*/, 
		const std::string& /*kind*/, 
		const std::string& /*volume*/, 
		const uint32_t& price, 
		const std::string& /*producer*/, 
		const std::string& /*locate_address*/,
		const uint32_t& /*insurance_day*/,
		const uint32_t& /*harvest_day*/,
		const uint32_t& /*cutting_day*/,
		const std::string& /*recipient*/,
		const uint32_t& /*phone_number*/);

	[[eosio::action]] void delrice(const std::string& /*qrtype*/, const uint64_t&/*order_no*/);
	[[eosio::action]] void viewrice(const std::string& /*qrtype*/, const uint64_t& /*order_no*/);
	[[eosio::action]] void printrice(const std::string& /*qrtype*/);
	[[eosio::action]] void collect();

};



