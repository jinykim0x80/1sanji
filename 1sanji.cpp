#include "1sanji.hpp"
void onesanji::add_rice(
		const uint64_t& order_no, 
		const std::string& brand, 
		const std::string& kind, 
		const std::string& volume, 
		const uint32_t& price, 
		const std::string& producer, 
		const std::string& locate_address,
		const uint32_t& insurance_day,
		const uint32_t& harvest_day,
		const uint32_t& cutting_day,
		const std::string& recipient,
		const uint32_t& phone_number)
{
	require_auth(_self);

	gold_rice gold_rice_table(_self,_self);
	eosio::print("emplace gold_rice_table\n");
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

void onesanji::add_rice(
		const uint64_t& order_no, 
		const std::string& brand, 
		const std::string& kind, 
		const std::string& volume, 
		const uint32_t& price, 
		const std::string& producer, 
		const std::string& locate_address,
		const uint32_t& insurance_day)
{
	require_auth(_self);
	black_rice black_rice_table(_self,_self);
	eosio::print("emplace black\n");
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


void onesanji::del_rice(const uint64_t& order_no, const std::string& qrtype/* false = black, true = gold*/){
	require_auth(_self);
	eosio_assert(qrtype == "black" || qrtype == "gold", "Invalid qrtype");
	if(qrtype == "black"){
		black_rice black_rice_table(_self,_self);
		eosio_assert(black_rice_table.get_code() == _self, "you don't access");

		auto iter = black_rice_table.find(order_no);
		eosio_assert(iter != black_rice_table.end(), "order_no doen't exist");
		black_rice_table.erase(iter);
		eosio::print(order_no, "is removed\n");

	}
	else if(qrtype == "gold"){
		gold_rice gold_rice_table(_self,_self);
		eosio_assert(gold_rice_table.get_code() == _self, "you don't access");

		auto iter = gold_rice_table.find(order_no);
		eosio_assert(iter != gold_rice_table.end(), "order_no doen't exist");
		gold_rice_table.erase(iter);
		eosio::print(order_no, "is removed\n");
	}
}
void onesanji::view_rice(const uint64_t& order_no, const std::string& qrtype /* false = black, true = gold*/){
	require_auth(_self);
	eosio_assert(qrtype == "black" || qrtype == "gold", "Invalid qrtype");
	if(qrtype == "black"){
		black_rice black_rice_table(_self,_self);
		
		auto iter = black_rice_table.find(order_no);
		eosio_assert(iter != black_rice_table.end(), "order_no not found");
		eosio::print("==========================================\n");
		eosio::print("order_no: ", iter->order_no, "\n");	
		eosio::print("brand: ", iter->brand, "\n");	
		eosio::print("volume: ", iter->volume, "\n");	
		eosio::print("kind: ", iter->kind, "\n");	
		eosio::print("price: ", iter->price, "\n");	
		eosio::print("producer: ", iter->producer, "\n");	
		eosio::print("locate_address: ", iter->locate_address, "\n");	
		eosio::print("insurance_day: ", iter->insurance_day, "\n");	
		eosio::print("==========================================\n\n");

	}
	else if(qrtype == "gold"){
		gold_rice gold_rice_table(_self,_self);
		
		auto iter = gold_rice_table.find(order_no);
		eosio_assert(iter != gold_rice_table.end(), "order_no not found");
		eosio::print("==========================================\n");
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
		eosio::print("==========================================\n\n");
	}
}

void onesanji::print_rice_tables(const std::string& qrtype) {
	require_auth(_self);
	eosio_assert(qrtype == "black" || qrtype == "gold", "Invalid qrtype");

	if(qrtype == "black"){
		black_rice black_rice_table(_self,_self);
		eosio_assert(black_rice_table.get_code() == _self, "you don't access");
		std::vector<uint64_t> primary_keys(0);
		for(const auto& i : black_rice_table){
			primary_keys.push_back(i.primary_key());	
		}
		for(const auto i : primary_keys){
			view_rice(i, "black");		
		}
	}
	else if(qrtype == "gold"){
		gold_rice gold_rice_table(_self,_self);
		eosio_assert(gold_rice_table.get_code() == _self, "you don't access");
		std::vector<uint64_t> primary_keys(0);
		for(const auto& i : gold_rice_table){
			primary_keys.push_back(i.primary_key());	
		}
		for(const auto i : primary_keys){
			view_rice(i, "gold");		
		}
	}
}
EOSIO_ABI(onesanji, (add_rice)(del_rice)(view_rice)(print_rice_tables))
