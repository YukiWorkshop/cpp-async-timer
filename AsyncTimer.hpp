/*
    This file is part of CPPAsyncTimer.
    Copyright (C) 2020 ReimuNotMoe

    This program is free software: you can redistribute it and/or modify
    it under the terms of the MIT License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#pragma once

#include <boost/asio.hpp>
#include <functional>

namespace YukiWorkshop {
	namespace AsyncTimer {
		class TimerContext {
		public:
			boost::asio::deadline_timer timer;
			std::function<void()> func;
			std::function<void(const boost::system::error_code &e)> func_wrapper;
			bool autofree = false;

			TimerContext(boost::asio::io_service &__io_svc) : timer(__io_svc) {

			}
		};

		void clearInterval(TimerContext *&__ctx) {
			if (__ctx) {
				__ctx->timer.cancel();
				__ctx = nullptr;
			}
		}

		void clearTimeout(TimerContext *&__ctx) {
			clearInterval(__ctx);
		}

		TimerContext *
		setInterval(boost::asio::io_service &__io_svc, const std::function<void()> &__func, size_t __interval) {
			auto *ctx = new TimerContext(__io_svc);
			ctx->func = __func;

			ctx->func_wrapper = [ctx, __interval](const boost::system::error_code &e) {
				if (e) {
					delete ctx;
					return;
				}

				ctx->timer.expires_from_now(boost::posix_time::milliseconds(__interval));
				ctx->timer.async_wait(ctx->func_wrapper);

				ctx->func();
			};

			ctx->timer.expires_from_now(boost::posix_time::milliseconds(__interval));
			ctx->timer.async_wait(ctx->func_wrapper);

			return ctx;
		}

		auto setTimeout(boost::asio::io_service &__io_svc, const std::function<void()> &__func, size_t __timeout) {
			auto *ctx = new TimerContext(__io_svc);
			ctx->autofree = true;
			ctx->func = __func;

			struct ret {
				operator TimerContext*() {
					ctx->autofree = false;
					return ctx;
				}

				TimerContext *ctx;
			};

			ctx->func_wrapper = [ctx, __timeout](const boost::system::error_code &e) {
				if (e) {
					delete ctx;
					return;
				}

				ctx->func();

				if (ctx->autofree)
					delete ctx;
			};

			ctx->timer.expires_from_now(boost::posix_time::milliseconds(__timeout));
			ctx->timer.async_wait(ctx->func_wrapper);

			return ret{ctx};
		}

	}
}