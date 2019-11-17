type state = {search: string};

type actions =
  | ChangeSearch(string);

let reducer = (_state, action) =>
  switch (action) {
  | ChangeSearch(newValue) => {search: newValue->String.lowercase}
  };

let initialState = {search: ""};
[@react.component]
let make = () => {
    let (state, dispatch) = React.useReducer(reducer, initialState);
    let changeSearch = _ => {
      open Utils.Debounce;
      let update =
        make(newValue => dispatch(ChangeSearch(newValue)), ~wait=250);
      newValue => update |> call(newValue);
    };
  <div className="main-panel">
    <div className="content-wrapper">
      <Header />
      <Search onChange={changeSearch()} />
      <div className="row">
        <div className="col-7 grid-margin"> <IceScreamSearch searchQuery=state.search /> </div>
      </div>
    </div>
  </div>;
};