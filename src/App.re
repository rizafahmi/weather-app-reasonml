[%bs.raw {|require('./App.css')|}];

[@bs.module] external logo : string = "./logo.svg";

type state = {weather: WeatherData.weather};
type action =
  | WeatherLoaded(WeatherData.weather);

let dummyWeather: WeatherData.weather = {
  summary: "Warn throughout the day",
  temp: 30.5,
};

let component = ReasonReact.reducerComponent("App");

let make = (~message, _children) => {
  ...component,
  initialState: () => {weather: dummyWeather},
  reducer: (action, _prevState) =>
    switch (action) {
    | WeatherLoaded(weather) => ReasonReact.Update({weather: weather})
    },
  render: ({state: {weather}}) =>
    <div className="App">
      <p> (ReasonReact.string(weather.summary)) </p>
    </div>,
};
