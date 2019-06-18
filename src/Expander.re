type state = {expanded: bool};
type action =
  | Toggle;

module Styles = {
  open Css;
  let expanded = style([maxHeight(pct(100.0))]);
  let notExpanded = style([maxHeight(pct(0.0)), display(none)]);
  let title =
    style([
      fontWeight(`bold),
      fontSize(px(16)),
      marginLeft(px(20)),
      color(Theme.textBlack),
      flexGrow(5.0),
      hover([textDecoration(underline)]),
    ]);
  let button =
    style([
      width(pct(100.0)),
      border(px(0), none, black),
      background(none),
      textAlign(`left),
      padding2(px(20), px(10)),
      display(`flex),
    ]);
  let content =
    style([
      paddingLeft(px(20)),
      paddingRight(px(20)),
      paddingBottom(px(10)),
      marginBottom(px(-1)),
    ]);
  let main = style([borderTop(px(1), solid, hex("d1d8db"))]);
  let chR = [
    display(inlineBlock),
    height(px(20)),
    unsafe("fill", "rgb(0, 139, 206)"),
    transform(rotateZ(deg(90))),
  ];
  let chevron = style(chR);
  let chevronDown =
    merge([chevron, style([transform(rotateZ(deg(270)))])]);


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
  <div className=Styles.main>
    <button
      type_="button" className=Styles.button onClick={_e => dispatch(Toggle)}>
      <Chevron style=Styles.(state.expanded ? chevronDown : chevron) />
      <span className=Styles.title> {ReasonReact.string(title)} </span>
    </button>
    <div
      className={state.expanded ? Styles.expanded : Styles.notExpanded}
      ariaExpanded={state.expanded}>
      <div className=Styles.content> children </div>
    </div>
  </div>;
};
