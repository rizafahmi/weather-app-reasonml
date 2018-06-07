[%bs.raw {|require('./App.css')|}];

[@bs.module] external logo : string = "./logo.svg";

type optionOrError('a) =
  | Some('a)
  | None
  | Error;
type state = {weather: optionOrError(WeatherData.weather)};
type action =
  | WeatherLoaded(WeatherData.weather)
  | WeatherError;

let dummyWeather: WeatherData.weather = {
  summary: "Warn throughout the day",
  temp: 30.5,
};

let component = ReasonReact.reducerComponent("App");

let make = (~message, _children) => {
  ...component,
  initialState: () => {weather: None},
  reducer: (action, _prevState) =>
    switch (action) {
    | WeatherLoaded(weather) => ReasonReact.Update({weather: Some(weather)})
    | WeatherError => ReasonReact.Update({weather: Error})
    },
  didMount: self => {
    let handleWeatherLoaded = weather => self.send(WeatherLoaded(weather));
    let handleWeatherError = () => self.send(WeatherError);
    WeatherData.getWeather()
    |> Js.Promise.then_(weather => {
         handleWeatherLoaded(weather);
         Js.Promise.resolve();
       })
    |> Js.Promise.catch(_err => {
         handleWeatherError();
         Js.Promise.resolve();
       })
    |> ignore;
    /* ReasonReact.NoUpdate; */
  },
  render: ({state: {weather}}) =>
    <div className="App">
      <p>
        (
          switch (weather) {
          | None => ReasonReact.string("Loading the weather...")
          | Some(weather) => ReasonReact.string(weather.summary)
          }
        )
      </p>
    </div>,
};
