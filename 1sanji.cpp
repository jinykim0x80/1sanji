#include "1sanji.hpp"
void onesanji::addrice(
		const std::string& qrtype,	
		const uint64_t& order_no, 
		const std::string& brand, 
		const std::string& kind, 
		const std::string& volume, 
		const uint32_t& price, 
		const std::string& producer, 
		const std::string& locate_address,
		const uint32_t& insurance_day,
		const uint32_t& harvest_day = NULL,
		const uint32_t& cutting_day = NULL,
		const std::string& recipient = NULL,
		const uint32_t& phone_number = NULL)
{
	require_auth(_self);
	eosio_assert(qrtype == "black" || qrtype == "gold", "Invalid qrtype");

	if(qrtype == "black"){
		black_rice black_rice_table(_self,_self);
		eosio_assert(black_rice_table.get_code() == _self, "you don't access");
		eosio::print(order_no, " is adding in black_rice_table\n");
		auto iter = black_rice_table.find(order_no);
		eosio_assert(iter == black_rice_table.end(), "order_no already exist");
		black_rice_table.emplace(_self, [&](auto& r){
			r.order_no = order_no;
			r.brand = brand;
			r.kind = kind;
			r.volume = volume;
			r.price = price;
			r.producer = producer;
			r.locate_address = locate_address;
			r.insurance_day = insurance_day;
		});
	}
	else if(qrtype == "gold"){
		gold_rice gold_rice_table(_self,_self);
		eosio_assert(gold_rice_table.get_code() == _self, "you don't access");
		eosio::print(order_no, " is adding in gold_rice_table\n");
		auto iter = gold_rice_table.find(order_no);
		eosio_assert(iter == gold_rice_table.end(), "order_no already exist");
		gold_rice_table.emplace(_self, [&](auto& r){
			r.order_no = order_no;
			r.brand = brand;
			r.kind = kind;
			r.volume = volume;
			r.price = price;
			r.producer = producer;
			r.locate_address = locate_address;
			r.insurance_day = insurance_day;
			r.harvest_day = harvest_day;
			r.cutting_day = cutting_day;
			r.recipient = recipient;
			r.phone_number = phone_number;
		});
	}
}

	
void onesanji::delrice(const std::string& qrtype, const uint64_t& order_no){
	require_auth(_self);
	eosio_assert(qrtype == "black" || qrtype == "gold", "Invalid qrtype");
	if(qrtype == "black"){
		black_rice black_rice_table(_self,_self);
		eosio_assert(black_rice_table.get_code() == _self, "you don't access");

		auto iter = black_rice_table.find(order_no);
		eosio_assert(iter != black_rice_table.end(), "order_no doen't exist");
		black_rice_table.erase(iter);

	}
	else if(qrtype == "gold"){
		gold_rice gold_rice_table(_self,_self);
		eosio_assert(gold_rice_table.get_code() == _self, "you don't access");

		auto iter = gold_rice_table.find(order_no);
		eosio_assert(iter != gold_rice_table.end(), "order_no doen't exist");
		gold_rice_table.erase(iter);
	}
}
void onesanji::viewrice(const std::string& qrtype, const uint64_t& order_no){
	require_auth(_self);
	eosio_assert(qrtype == "black" || qrtype == "gold", "Invalid qrtype");
	if(qrtype == "black"){
		black_rice black_rice_table(_self,_self);
		auto iter = black_rice_table.find(order_no);
		eosio_assert(iter != black_rice_table.end(), "order_no not found");
		eosio::print("=========================================\n");
		eosio::print("Black Rice\n");
		eosio::print("=========================================\n");
		eosio::print("order_no: ", iter->order_no, "\n");	
		eosio::print("brand: ", iter->brand, "\n");	
		eosio::print("volume: ", iter->volume, "\n");	
		eosio::print("kind: ", iter->kind, "\n");	
		eosio::print("price: ", iter->price, "\n");	
		eosio::print("producer: ", iter->producer, "\n");	
		eosio::print("locate_address: ", iter->locate_address, "\n");	
		eosio::print("insurance_day: ", iter->insurance_day, "\n");	
		eosio::print("=========================================\n");

	}
	else if(qrtype == "gold"){
		//eosio_assert(gold_rice_table.get_code() == "onesanji1234"_n, "you don't access");
		gold_rice gold_rice_table(_self,_self);
		auto iter = gold_rice_table.find(order_no);
		eosio_assert(iter != gold_rice_table.end(), "order_no not found");

		eosio::print("=========================================\n");
		eosio::print("Gold Rice\n");
		eosio::print("=========================================\n");
		eosio::print("order_no: ", iter->order_no, "\n");	
		eosio::print("brand: ", iter->brand, "\n");	
		eosio::print("volume: ", iter->volume, "\n");	
		eosio::print("kind: ", iter->kind, "\n");	
		eosio::print("price: ", iter->price, "\n");	
		eosio::print("producer: ", iter->producer, "\n");	
		eosio::print("locate_address: ", iter->locate_address, "\n");	
		eosio::print("insurance_day: ", iter->insurance_day, "\n");	
		eosio::print("harvest_day: ", iter->harvest_day, "\n");	
		eosio::print("cutting_day: ", iter->cutting_day, "\n");	
		eosio::print("recipient: ", iter->recipient, "\n");	
		eosio::print("phone_number: ", iter->phone_number, "\n");		
		eosio::print("=========================================\n");
	}
}

void onesanji::printalltable(const std::string& qrtype) {
	require_auth(_self);
	std::vector<uint64_t> black_primary_keys(0);
	std::vector<uint64_t> gold_primary_keys(0);

	if(qrtype == "black"){								// black only
		black_rice black_rice_table(_self,_self);
		for(const auto& i : black_rice_table){
			black_primary_keys.push_back(i.primary_key());	
		}
		for(auto i : black_primary_keys){
			viewrice("black", i);		
		}
	}
	else if(qrtype == "gold"){							// gold only
		gold_rice gold_rice_table(_self,_self);
		for(const auto& i : gold_rice_table){
			gold_primary_keys.push_back(i.primary_key());	
		}
		for(auto i : gold_primary_keys){
			viewrice("gold", i);		
		}
	}
	else{												// both
		black_rice black_rice_table(_self,_self);
		for(const auto& i : black_rice_table){
			black_primary_keys.push_back(i.primary_key());	
		}
		for(auto i : black_primary_keys){
			viewrice("black", i);		
		}

		gold_rice gold_rice_table(_self,_self);
		for(const auto& i : gold_rice_table){
			gold_primary_keys.push_back(i.primary_key());	
		}
		for(auto i : gold_primary_keys){
			viewrice("gold", i);		
		}
	}
	
}
EOSIO_ABI(onesanji, (addrice)(delrice)(viewrice)(printalltable))

