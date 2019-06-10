type state = {expanded: bool};
type action = Toggle(bool);

[@react.component]
let make = (~children, ~title) => {
    let (state, dispatch) =
    React.useReducer(
      (_state, action) =>
        switch (action) {
        | Toogle(e) => {expanded: not(state.expanded)}
        },
      {expanded: false},
    ); 
    <div>
    <h2>{ReasonReact.string(title)}</h2>
    children
    </div>
}