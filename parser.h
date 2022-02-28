#pragma once

#include "object.h"
#include "tokenizer.h"

#include <memory>
#include <queue>

std::shared_ptr<Object> MakeCell(std::queue<std::shared_ptr<Object>>& objects);

std::shared_ptr<Object> Read(Tokenizer* tokenizer);

std::shared_ptr<Object> ReadList(Tokenizer* tokenizer);