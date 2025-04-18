#pragma once

#define CLONE(Instance, Parent) public: \
								Parent* GetClone() const override { return new Instance(*this); }

#define DONTCOPY(Instance) public: \
							Instance(const Instance&) = delete;\
							Instance(Instance&&) = delete;\
							Instance& operator = (const Instance&) = delete;\
							Instance& operator = (Instance&&) = delete;