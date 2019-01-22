#include "1sanji.hpp"
void onesanji::addrice(
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
		uint32_t& phone_number)
{
	gold_rice gold_rice_table(_self,_self);
	eosio_assert(gold_rice_table.get_code() == _self, "you don't access");
	eosio::print("addrice called\n");
	eosio::print("emplace gold_rice_table\n");
	auto iter = gold_rice_table.find(order_no);
	eosio_assert(iter == gold_rice_table.end(), "order_no already exist");
//	gold_rice gold_rice_table(_self,_self);
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

void onesanji::delrice(uint64_t& order_no, const std::string& qrtype/* false = black, true = gold*/){
	eosio_assert(qrtype == "black" || qrtype == "gold", "Invalid qrtype");
	eosio::print("delrice called\n");
	if(qrtype == "black"){
		print("It is gold\n");
	}
	else if(qrtype == "gold"){
		//gold_rice gold_rice_table(_self, _self);
		//
		gold_rice gold_rice_table(_self,_self);
		eosio_assert(gold_rice_table.get_code() == _self, "you don't access");

		auto iter = gold_rice_table.find(order_no);
		eosio_assert(iter != gold_rice_table.end(), "order_no doen't exist");
		gold_rice_table.erase(iter);
	}
}
void onesanji::viewrice(uint64_t& order_no, const std::string& qrtype /* false = black, true = gold*/){
	eosio_assert(qrtype == "black" || qrtype == "gold", "Invalid qrtype");
	eosio::print("viewrice called\n");
	if(qrtype == "black"){

	}
	else if(qrtype == "gold"){
		//gold_rice gold_rice_table(_self,_self);
		//eosio_assert(gold_rice_table.get_code() == "onesanji1234"_n, "you don't access");
		gold_rice gold_rice_table(_self,_self);
		
		auto iter = gold_rice_table.find(order_no);
		eosio_assert(iter != gold_rice_table.end(), "order_no not found");
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
		eosio::print("printing finish\n");
	}
}

void onesanji::printalltable() {
	//gold_rice gold_rice_table(_self,_self);
	gold_rice gold_rice_table(_self,_self);
	eosio_assert(gold_rice_table.get_code() == _self, "you don't access");
	eosio::print("pprintalltable called\n");
	std::vector<uint64_t> primary_keys(0);
	for(const auto& i : gold_rice_table){
		primary_keys.push_back(i.primary_key());	
	}
	for(auto i : primary_keys){
		viewrice(i, "gold");		
	}
}
EOSIO_ABI(onesanji, (addrice)(delrice)(viewrice)(printalltable))
