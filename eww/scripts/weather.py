import python_weather

import asyncio
import os


async def getweather():
    # declare the client. the measuring unit used defaults to the metric system (celcius, km/h, etc.)
    async with python_weather.Client() as client:
        # fetch a weather forecast from a city
        weather = await client.get("Saint Petersburg")

        # returns the current day's forecast temperature (int)
        return weather

        # get the weather forecast for a few days
        # for daily in weather.daily_forecasts:
        # print(daily)

        # hourly forecasts
        # for hourly in daily.hourly_forecasts:
        # print(f' --> {hourly!r}')


def return_emoji(weather):
    if weather.description == "Sunny":
        return ""
    elif weather.description == "Partly cloudy":
        if weather.datetime.hour > 19 or weather.datetime.hour < 6:
            return "󰼱"
        else:
            return "󰖕"
    elif weather.description == "Cloudy":
        return "󰖐"
    elif weather.description == "Very cloudy" or weather.description == "Overcast":
        return "󰅟"
    elif weather.description == "Fog" or weather.description == "Mist":
        return "󰖑"
    elif weather.description == "Light rain shower" or weather.description == "Patchy rain nearby":
        if weather.datetime.hour > 19 or weather.datetime.hour < 6:
            return ""
        else:
            return ""
    elif (
        weather.description == "Light sleet shower"
        or weather.description == "Light Sleet"
    ):
        if weather.datetime.hour > 19 or weather.datetime.hour < 6:
            return ""
        else:
            return ""
    elif weather.description == "Thundery shower" or "Thundery outbreaks in nearby":
        if weather.datetime.hour > 19 or weather.datetime.hour < 6:
            return ""
        else:
            return ""
    elif weather.description == "Light snow":
        if weather.datetime.hour > 19 or weather.datetime.hour < 6:
            return ""
        else:
            return ""
    elif weather.description == "Heavy snow":
        return "󰼶"
    elif weather.description == "Heavy rain":
        return ""
    elif weather.description == "Light snow shower":
        return "󰼴"
    elif weather.description == "Heavy snow shower":
        return ""
    elif weather.description == "Rain with thunderstorm" or weather.description == "Light rain with thunderstorm" or weather.description == "Light rain shower, rain with thunderstorm":
        return ""
    elif weather.description == "Thundery snow shower":
        return ""
    elif weather.description == "Clear":
        if weather.datetime.hour > 19 or weather.datetime.hour < 6:
            return ""
        else:
            return ""
    else:
        return ""


if __name__ == "__main__":
    weather = asyncio.run(getweather())
    # print(weather.description)
    print(f"{return_emoji(weather)}  {weather.temperature}°C")
