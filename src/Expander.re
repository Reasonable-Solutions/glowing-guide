type state = { expanded: bool };
type action =
  | Toggle;

module Styles = {
  open Css;
  let expanded = style([maxHeight(pct(100.0))]);
  let notExpanded = style([maxHeight(pct(0.0)), display(none)]);
};
[@react.component]
let make = (~children, ~title) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch ((action: action)) {
        | Toggle => {expanded: !state.expanded}
        },
      {expanded: false},
    );
  <div className="menuExpander">
    <button
      type_="button"
      className="minus expanderButton"
      onClick={_e => dispatch(Toggle)}>
      {ReasonReact.string(title)}
    </button>
    <div className={state.expanded ? Styles.expanded : Styles.notExpanded}>
      <div className="content"> {children} </div>
    </div>
  </div>;
};
