type state = {expanded: bool};
type action =
  | Toggle;

[@react.component]
let make = (~children, ~title) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch ((action: action)) {
        | Toggle => {expanded: (!state.expanded)}
        },
      {expanded: false},
    );
  <div> <h2> {ReasonReact.string(title)} </h2> children </div>;
};
