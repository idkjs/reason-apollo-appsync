module Styles = {
  let app = ReactDOMRe.Style.make(~textAlign="center", ());
  let container =
    ReactDOMRe.Style.make(
      ~padding="10px",
      ~borderBottom="1px solid #ddd",
      (),
    );
  let title = ReactDOMRe.Style.make(~fontSize="18px", ());
  let description =
    ReactDOMRe.Style.make(~fontSize="15px", ~color="rgba(0, 0, 0, .5)");

  let inputStyle =
    ReactDOMRe.Style.make(
      ~height="40px",
      ~width="300px",
      ~padding="7px",
      ~fontSize="15px",
      ~outline="none",
      (),
    );
};
open Styles;
type state = {value: string};

type action =
  | ChangeValue(string);

let initialState = {value: "choco"};
let reducer = (_state, action) =>
  switch (action) {
  | ChangeValue(newValue) => {value: newValue}
  };
[@react.component]
let make = (~onChange=_newValue => ()) => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  <div>
    <input
      style=inputStyle
      placeholder="Search for ice cream"
      value=state.value
      onChange={
        e => {
          let value = ReactEvent.Form.target(e)##value;
          dispatch(ChangeValue(value));
          onChange(value);
        }
      }
    />
  </div>;
};